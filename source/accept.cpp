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

Accept::Accept(unique_char uniqueType) : Unique(uniqueType), Sync(), m_pEpoll(NULL),
	m_tempReadPacket(NULL), m_isIdentify(false) {
	memset(&m_socket, 0, sizeof(struct SocketInformation));
	clearStateOutFlag();
}
Accept::~Accept(void){
	releasePacket();
	SAFE_RELEASE(m_tempReadPacket)
}
void Accept::releasePacket(void){
	this->lock();
	for( auto pPacket : m_packetQueue ){
		pPacket->release();
	}
	m_packetQueue.clear();
	this->unlock();
}
void Accept::receivePacket(Packet* pPacket){
	pPacket->resetCursor();		// 后面的写操作需要重置
	pPacket->retain();			// 进入队列前引用
	this->lock();
	m_packetQueue.push_back(pPacket);
	this->unlock();
	m_pEpoll->changeStateOut(this);	// 更改epoll状态，等待可写
}
bool Accept::tryReadSocket(void){
	if( !readSocket() ){
		removeSocket();
		return false;
	}
	return true;
}
bool Accept::tryWriteSocket(void){
	Packet* pPacket = NULL;
	this->lock();
	if( !m_packetQueue.empty() ){
		pPacket = m_packetQueue.front();
		pPacket->retain();		// 引用 1
	}
	this->unlock();
	if( NULL == pPacket ){
		m_pEpoll->changeStateIn(this);
		return true;
	}
	if( !writeSocket(pPacket) ){
		pPacket->release();		// 释放 1
		removeSocket();
		return false;
	}
	if( pPacket->isCursorEnd() ){
		pPacket->release();		// 释放 1
		// 反向检查队列并移除队末尾的对象
		bool releasePacketAtEnd = false;
		this->lock();
		if( !m_packetQueue.empty() && m_packetQueue.front() == pPacket ){
			releasePacketAtEnd = true;
			m_packetQueue.pop_front();
		}
		this->unlock();
		if(releasePacketAtEnd){
			pPacket->release();	// 对应进入队列时的retain
		}
		return true;
	}
	return true;
}
void Accept::removeSocket(void){
	m_pEpoll->changeStateRemove(this);	// 修改epoll中的状态，不再接收数据
	m_pEpoll->tryRemoveSocket(this);
}
void Accept::resetData(void){
	closeSocket();	// 关闭套接字
	SAFE_RELEASE(m_tempReadPacket)
	m_isIdentify = false;
	releasePacket();	// 取消所有数据包的发送
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
    		pPacket->release();		// 对应Packet创建时的retain
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
			pPacket->retain();	// 如果数据没有全部收到，那么m_tempReadPacket会保持这个retain状态
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
