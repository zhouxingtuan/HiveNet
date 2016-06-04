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

Accept::Accept(Epoll* pEpoll) : HandlerInterface(), m_pEpoll(pEpoll){
	memset(&m_socket, 0, sizeof(struct SocketInformation));
}
Accept::~Accept(void){

}
void Accept::onInitialize(void){

}
void Accept::onDestroy(void){
	closeSocket();	// 关闭套接字
	// 修改epoll中的状态
}
void Accept::readSocket(void){
	char recvBuffer[8192];
    char* recvBufferPtr;
    int nread;
    int writeLength;
    Packet* pPacket;
    int fd = m_socket.fd;
    pPacket = m_tempReadPacket;
    if( pPacket == NULL ){
        nread = read(fd, recvBuffer, 8192);
    }else{
        nread = read(fd, pPacket->getCursorPtr(), pPacket->getLength()-pPacket->getCursor());
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
    }else{

    }

    if( pMessage == NULL ){
        //如果读取的消息长度不到 MESSAGE_HEAD_LENGTH ，那么抛弃该消息
        if( nread < MESSAGE_HEAD_LENGTH ){
            return true;
        }
        //这里读取的信息很可能包含多条信息，这时候需要解析出来；这几条信息因为太短，在发送时被底层socket合并了
        recvBufferPtr = recvBuffer;
        do{
            // 先解密头部数据
            if( CONNECTION_SERVICE_TO_SERVICE != pAgent->getConnectionType() ){
                need_decrypt = true;
            }else{
                // group client的第一条消息（服务端发来的identify消息）使用这个字段判定对头部解密
                if( pAgent->isForbiddenReceive() ){
                    pAgent->setForbiddenReceive(false);
                    need_decrypt = true;
                }else{
                    need_decrypt = false;
                }
            }
            if( need_decrypt ){
                Security::decrypt(recvBufferPtr, Security::getKey());
            }
            pHead = (MessageHead*)( (void*)(recvBufferPtr) );
            if( pHead->function > RPC_FUNCTION_SIZE ){  // 与其检测长度，不如直接检测方法
                break;
            }
            writeLength = std::min( (int)(nread-(recvBufferPtr-recvBuffer)), (int)pHead->length );
            pMessage = createMessage( pHead->length );
            // 将数据拷贝到message中
            pMessage->write( recvBufferPtr, writeLength );
            pMessage->setTotalLength( pHead->length );
            pMessage->setSource( pAgent );   // 这里直接设置消息的回调接收对象
            pMessage->getBufferPtr()->setHeadEncrypt( false );

            recvBufferPtr += writeLength;
            if( pMessage->isCursorEnd() ){
                // 统一对消息进行解密，目前加密和解密统一由epoll线程来承担
                if( need_decrypt ){
                    pMessage->getBufferPtr()->setValueEncrypt( true );  // 所有网络通信消息都是经过加密的
                    pMessage->getBufferPtr()->decryptValue();
                }
                m_pDispatcher->receiveMessage(pMessage);
                pMessage = NULL;
            }
        }while(nread-(recvBufferPtr-recvBuffer) > MESSAGE_HEAD_LENGTH);
    }else{
        pMessage->moveCursor(nread);// move the cursor
    }
    if( pMessage != NULL && pMessage->isCursorEnd() ){
        // 统一对消息进行解密，目前加密和解密统一由epoll线程来承担
        if( CONNECTION_SERVICE_TO_SERVICE != pAgent->getConnectionType() ){
            pMessage->getBufferPtr()->setValueEncrypt( true );  // 所有网络通信消息都是经过加密的
            pMessage->decrypt();
        }
        m_pDispatcher->receiveMessage(pMessage);
        pMessage = NULL;
    }
    pAgent->setTempMessage(pMessage);  // 设置当前agent的临时消息数据
    return true;
}
void Accept::writeSocket(void){

}
void Accept::closeSocket(void){
	if( m_socket.fd != 0 ){
        close( m_socket.fd );
        m_socket.fd = 0;
    }
}

NS_HIVENET_END
