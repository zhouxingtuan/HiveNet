//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/31
// Time: 下午10:15
// To change this template use File | Settings | File Templates.
//

#include "epoll.h"

NS_HIVENET_BEGIN

static Epoll* g_pEpoll = NULL;
Epoll::Epoll() : HandlerInterface(), m_curfds(0), m_epollfd(0) {
	memset(&m_socket, 0, sizeof(struct SocketInformation));
}
Epoll::~Epoll(){
	closeListenSocket();  // 关闭套接字
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
void Epoll::onInitialize(void){
	if( 0 == m_socket.port ){
		fprintf(stderr, "--Epoll::onInitialize socket ip and port is not set yet\n");
		return;
	}
	if( !initListenSocket() ){
		fprintf(stderr, "--Epoll::onInitialize initListenSocket failed\n");
		return;
	}
	if( !createEpoll() ){
		fprintf(stderr, "--Epoll::onInitialize socket createEpoll failed\n"); // epoll 创建失败
		return;
	}
}
void Epoll::onDestroy(void){
	closeListenSocket();
}
void Epoll::onUpdate(void){
	if( !waitEpoll() ){
		return;
	}
}
bool Epoll::sendPacket(unsigned int handle, Packet* pPacket){
	return false;
}
unsigned int Epoll::createClient(const char* ip, unsigned short port){

	return -1;
}
void Epoll::closeClient(unsigned int handle){

}
void Epoll::closeAccept(unsigned int handle){

}
bool Epoll::createEpoll(void){
    m_epollfd = epoll_create(MAX_LISTEN_SIZE);
    // 检查是否需要添加监听端口
    if( m_socket.port == 0 ){
        return true;
    }
    if( epollAdd(m_epollfd, m_socket.fd, this) < 0 ){
        close(m_epollfd);
        m_epollfd = 0;
        fprintf(stderr, "--Epoll::create bind socket error ip(%s) port(%d)\n", m_socket.ip, m_socket.port);
        return false;
    }
    ++m_curfds;
//    fprintf(stderr,"--Epoll::create bind socket ok fd(%d) ip(%s) port(%d)\n", m_socket.fd, m_socket.ip, m_socket.port);
    return true;
}
bool Epoll::waitEpoll(void){
    void* ptr;
    struct epoll_event* pEvent;
    int n;
    int nfds;
    nfds = epoll_wait(m_epollfd, m_events, MAX_EPOLL_EVENT, EPOLL_WAIT_FLAG);
    if(nfds < 0){
        fprintf(stderr, "epoll_wait error\n");
        return false;
    }
    for(n=0; n < nfds; ++n){
        pEvent = &m_events[n];
        ptr = pEvent->data.ptr;
        if(ptr == NULL){
            fprintf(stderr, "we have and empty ptr\n");
            continue;   // 这个会发生吗？
        }
        if(ptr == this){
//            if( acceptSocket() ){
//                continue;
//            }else{
//                return false;
//            }
        }
        if(pEvent->events & EPOLLIN){
//            if( !readMessage( (Agent*)ptr ) ){
//                removeSocket( (Agent*)ptr );
//                continue;
//            }
        }
        if(pEvent->events & EPOLLOUT){
//            if( !writeMessage( (Agent*)ptr ) ){
//                removeSocket( (Agent*)ptr );
//            }
            continue;
        }else if(pEvent->events & EPOLLERR){
//            removeSocket( (Agent*)ptr );
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
    if( m_epollfd != 0 ){
        close(m_epollfd);
        m_epollfd = 0;
    }
}

NS_HIVENET_END
