//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/31
// Time: 下午9:40
// To change this template use File | Settings | File Templates.
//

#include "accept.h"
#include "epoll.h"

NS_HIVENET_BEGIN

Accept::Accept(Epoll* pEpoll) : HandlerInterface(), m_pEpoll(pEpoll),
	m_tempReadPacket(NULL), m_isIdentify(false){
	memset(&m_socket, 0, sizeof(struct SocketInformation));
	clearStateOutFlag();
	m_handlerType = SOCKET_HANDLER_ACCEPT;
}
Accept::~Accept(void){
	SAFE_RELEASE(m_tempReadPacket)
}
bool Accept::onInitialize(void){
	return true;
}
bool Accept::onDestroy(void){
	return true;
}
bool Accept::onReadSocket(void){
	if( !readSocket() ){
		removeSocket();
	}
	return true;
}
bool Accept::onWriteSocket(Packet* pPacket){
    if( NULL == pPacket ){
    	m_pEpoll->changeStateIn(this);
    	return true;
    }
	if( !writeSocket(pPacket) ){
		removeSocket();
		return true;
	}
	if( pPacket->isCursorEnd() ){
		return true;
	}
	return false;	// 没有写完保留任务在队列中，继续写
}
void Accept::removeSocket(void){
	m_pEpoll->changeStateRemove(this);	// 修改epoll中的状态，不再接收数据
	// 生成一个任务，负责移除epoll中的这个socket对象
//	TaskRemoveSocket* pTask = new TaskRemoveSocket(m_pEpoll, this);
//	pTask->commitTask();
	m_pEpoll->onRemoveSocket(this);
}
void Accept::resetData(void){
	increaseVersion();	// 增加版本
	closeSocket();	// 关闭套接字
	SAFE_RELEASE(m_tempReadPacket)
	releaseTask();	// 取消所有任务的处理
}
void Accept::dispatchPacket(Packet* pPacket){
	m_pEpoll->receivePacket(getHandle(), pPacket);
}
bool Accept::readSocket(void){
	char recvBuffer[8192];
    char* recvBufferPtr;
    int nread;
    int packetLength;
    int writeLength;
    Packet* pPacket;
    pPacket = m_tempReadPacket;
    if( pPacket == NULL ){
        nread = read(m_socket.fd, recvBuffer, 8192);
    }else{
        nread = read(m_socket.fd, pPacket->getCursorPtr(), pPacket->getLength()-pPacket->getCursor());
    }
    if(nread < 0){
        switch(errno){
        case EINTR: return true; // 读数据失败，处理信号中断
        case EAGAIN:    // 可以下次重新调用
            return true;
        default: return false;
        }
        return false;
    }else if(nread == 0){
        return false;
    }
    //check stick message
    if( NULL != pPacket ){
    	pPacket->moveCursor(nread);
    	if( pPacket->isCursorEnd() ){
			// 派发消息给对应的消息处理器
			dispatchPacket(pPacket);
    		pPacket->release();
			pPacket = NULL;
    	}
    }else{
		if( nread < PACKET_HEAD_LENGTH ){
			return true;
		}
		//这里读取的信息很可能包含多条信息，这时候需要解析出来；这几条信息因为太短，在发送时被底层socket合并了
		recvBufferPtr = recvBuffer;
        do{
            packetLength = *(int*)((void*)(recvBufferPtr));
			if( packetLength < PACKET_HEAD_LENGTH || packetLength > getMaxLength() ){
				break;	// 这里直接将数据丢弃
			}
            writeLength = std::min( (int)(nread-(recvBufferPtr-recvBuffer)), packetLength );
			// 创建Packet对象，并将数据写入
			pPacket = new Packet(packetLength);
			pPacket->retain();
			pPacket->write( recvBufferPtr, writeLength );
            recvBufferPtr += writeLength;
            if( pPacket->isCursorEnd() ){
                // 派发消息给对应的消息处理器
				dispatchPacket(pPacket);
                pPacket->release();
                pPacket = NULL;
            }
            // 如果消息没有全部接收，那么将会放到临时包中等待下一次读数据操作
        }while(nread-(recvBufferPtr-recvBuffer) > PACKET_HEAD_LENGTH);
    }
	m_tempReadPacket = pPacket;
    return true;
}
bool Accept::writeSocket(Packet* pPacket){
    int nwrite;
    nwrite = write(m_socket.fd, pPacket->getCursorPtr(), pPacket->getLength()-pPacket->getCursor());
    if(nwrite < 0){
        switch(errno){
        case EINTR: return true; // 写数据失败，处理信号中断
        case EAGAIN:    // 可以下次重新调用
//            fprintf(stderr, "write EAGAIN capture\n");
            return true;
        default: return false;
        }
        return false;
    }
    pPacket->moveCursor( nwrite );// used
    return true;
}
void Accept::closeSocket(void){
	if( m_socket.fd != 0 ){
        close( m_socket.fd );
        m_socket.fd = 0;
    }
}

NS_HIVENET_END
