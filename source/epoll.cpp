//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/31
// Time: 下午10:15
// To change this template use File | Settings | File Templates.
//

#include "epoll.h"

NS_HIVENET_BEGIN
/*--------------------------------------------------------------------*/
static Epoll* g_pEpoll = NULL;
Epoll::Epoll() : RefObject(), m_pFactory(NULL), m_curfds(0), m_epollfd(0), m_exitNow(false) {
	memset(&m_socket, 0, sizeof(struct SocketInformation));
}
Epoll::~Epoll(){
	closeEpoll();  // 关闭套接字
}
Epoll* Epoll::getInstance(void){
	return g_pEpoll;
}
Epoll* Epoll::createInstance(void){
	if(g_pEpoll == NULL){
		g_pEpoll = new Epoll();
		SAFE_RETAIN(g_pEpoll)
	}
	return g_pEpoll;
}
void Epoll::destroyInstance(void){
    SAFE_RELEASE(g_pEpoll)
}
bool Epoll::initialize(void){
	if( 0 == m_socket.port ){
		fprintf(stderr, "--Epoll::onInitialize socket ip and port is not set yet\n");
		return false;
	}
	if( !initListenSocket() ){
		fprintf(stderr, "--Epoll::onInitialize initListenSocket failed\n");
		return false;
	}
	if( !createEpoll() ){
		fprintf(stderr, "--Epoll::onInitialize socket createEpoll failed\n"); // epoll 创建失败
		return false;
	}
	return true;
}
bool Epoll::update(void){
	if( isEpollExit() ){
		return false;
	}
	if( !waitEpoll() ){
		return false;
	}
	return true;
}
bool Epoll::tryRemoveSocket(Accept* pAccept){
	// 根据对象的类型，分类设置这个对象到idle中等待被使用
	unique_char handlerType = pAccept->getType();
	if( UNIQUE_HANDLER_ACCEPT == handlerType ){
		TaskInterface* pTask = m_pFactory->createAcceptOut(pAccept->getHandle());
		pTask->commitTask();
		idleConnect(pAccept);
	}else if( UNIQUE_HANDLER_CLIENT == handlerType ){
		TaskInterface* pTask = m_pFactory->createClientOut(pAccept->getHandle());
		pTask->commitTask();
		idleConnect(pAccept);
	}else{
		fprintf(stderr, "--Epoll::tryRemoveSocket unknown handler type\n");
	}
	pAccept->resetData();	// 重置对象的数据
	--m_curfds;
	return true;
}
bool Epoll::sendPacket(unique_long handle, Packet* pPacket){
	Accept* pAccept = getAccept(handle);
	if( NULL == pAccept ){
		return false;
	}
	pAccept->receivePacket(pPacket);
	return true;
}
void Epoll::setIdentify(unique_long handle, bool identify){
	Accept* pAccept = getAccept(handle);
	if( NULL == pAccept ){
		return;
	}
	pAccept->setIdentify(identify);
}
unique_long Epoll::createClient(const char* ip, unsigned short port){
	Client* pClient = createClient();
	unique_long handle = pClient->getHandle();
	pClient->setSocket(ip, port);
	// 生成连接任务，让线程来处理连接；这样做的原因是，某些连接地址不可到达，这时会占用（挂起）大量时间
	if( Thread::staticThread(Client::syncConnectServer, pClient) == 0 ){
		fprintf(stderr, "--Epoll::createClient Thread::staticThread failed\n");
		tryRemoveSocket(pClient);
		return INVALID_UNIQUE_HANDLE;
	}
	return handle;
}
void Epoll::closeClient(unique_long handle){
	Client* pClient = getClient(handle);
	if( NULL != pClient ){
		pClient->removeSocket();
	}
}
void Epoll::closeAccept(unique_long handle){
	Accept* pAccept = getAccept(handle);
	if( NULL != pAccept ){
		pAccept->removeSocket();
	}
}
bool Epoll::receivePacket(unique_long handle, Packet* pPacket){
	if( NULL == m_pFactory ){
		fprintf(stderr, "--Epoll::receivePacket m_pFactory is NULL\n");
		return false;
	}
	pPacket->resetCursor();		// 后面的读操作需要重置
	TaskInterface* pTask = m_pFactory->createPacketIn(handle, pPacket);
	pTask->commitTask();
	return true;
}
bool Epoll::receiveClient(Client* pClient){
	int fd = pClient->getSocketFD();
    if(fd < 0){
        return false;
    }
    if(m_curfds >= MAX_LISTEN_SIZE){
        close(fd);
        return false;
    }
    if(setNonBlocking(fd) < 0){
        close(fd);
        return false;
    }
    if( epollAdd(m_epollfd, fd, pClient) < 0 ){
        close(fd);
        return false;
    }
    ++m_curfds;
    TaskInterface* pTask = m_pFactory->createClientIn(pClient->getHandle());
	pTask->commitTask();
    return true;
}
bool Epoll::acceptSocket(void){
	struct sockaddr_in cliaddr;
	socklen_t socklen = sizeof(struct sockaddr_in);
	int fd;
	fd = accept(m_socket.fd, (struct sockaddr*)&cliaddr, &socklen);
	if(fd < 0){
		return true;
	}
    if(m_curfds >= MAX_LISTEN_SIZE){
        close(fd);
        return true;
    }
	if(setNonBlocking(fd) < 0){
		close(fd);
		return true;
	}
	// 获取一个连接对象Accept，将对象一并加入到epoll中
	Accept* pAccept = createAccept();
	if( epollAdd(m_epollfd, fd, pAccept) < 0 ){
		close(fd);
		idleConnect(pAccept);
		return false;
	}
	++m_curfds;
	pAccept->setSocketFD( fd );
	pAccept->setSocket( inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port );
    TaskInterface* pTask = m_pFactory->createAcceptIn(pAccept->getHandle());
	pTask->commitTask();
	return true;
}
bool Epoll::createEpoll(void){
    m_epollfd = epoll_create(MAX_LISTEN_SIZE);
    // 检查是否需要添加监听端口
    if( m_socket.fd == 0 ){
        return false;
    }
    if( epollAdd(m_epollfd, m_socket.fd, this) < 0 ){
        close(m_epollfd);
        m_epollfd = 0;
        fprintf(stderr, "--Epoll::create bind socket error ip(%s) port(%d)\n", m_socket.ip, m_socket.port);
        return false;
    }
    ++m_curfds;
    return true;
}
bool Epoll::waitEpoll(void){
    void* ptr;
    struct epoll_event* pEvent;
    int n;
    int nfds;
    nfds = epoll_wait(m_epollfd, m_events, MAX_EPOLL_EVENT, EPOLL_WAIT_FLAG);
    if(nfds < 0){
        return true;	// nothing happened
    }
    for(n=0; n < nfds; ++n){
        pEvent = &m_events[n];
        ptr = pEvent->data.ptr;
        if(ptr == NULL){
            fprintf(stderr, "we have an empty ptr\n");
            continue;   // 这个会发生吗？
        }
        if(ptr == this){
            if( acceptSocket() ){
                continue;
            }else{
                return false;
            }
        }
        if(pEvent->events & EPOLLIN){
        	((Accept*)ptr)->tryReadSocket();
        }
        if(pEvent->events & EPOLLOUT){
        	((Accept*)ptr)->tryWriteSocket();
            continue;
        }else if(pEvent->events & EPOLLERR){
        	((Accept*)ptr)->removeSocket();
            continue;
        }
    }//end handle events for loop
    return true;
}
bool Epoll::initListenSocket(void){
    int opt;
    int fd;
    struct sockaddr_in servaddr;
    socklen_t socklen = sizeof(struct sockaddr_in);
    bzero(&servaddr, socklen);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr( m_socket.ip );//htonl(INADDR_ANY);
    servaddr.sin_port = htons( m_socket.port );
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1){
		fprintf(stderr, "--Epoll::initListenSocket failed ip(%s) port(%d)\n", m_socket.ip, m_socket.port);
		return false;
    }
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if(setNonBlocking(fd) < 0){
		fprintf(stderr, "--Epoll::initListenSocket setNonBlocking to listen socket failed\n");
		goto SOCK_FAILED;
    }
    if(bind(fd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr)) == -1){
		fprintf(stderr, "--Epoll::initListenSocket bind listen socket error\n");
		goto SOCK_FAILED;
    }
    if(listen(fd, MAX_LISTEN_SIZE) == -1){
  		fprintf(stderr, "--Epoll::initListenSocket socket listen error\n");
		goto SOCK_FAILED;
    }
    fprintf(stderr, "--Epoll::initListenSocket OK ip=%s port=%d\n", m_socket.ip, m_socket.port);
    m_socket.fd = fd;
    return true;
SOCK_FAILED:
    close(fd);
    return false;
}
void Epoll::closeListenSocket(void){
    if(m_socket.fd != 0){
        epollRemove(m_epollfd, m_socket.fd);
        close(m_socket.fd);
        m_socket.fd = 0;
    }
}
void Epoll::closeEpoll(void){
	closeListenSocket();
    if( m_epollfd != 0 ){
        close(m_epollfd);
        m_epollfd = 0;
    }
    setEpollExit(true);
}

NS_HIVENET_END
