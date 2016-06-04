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
	// 添加对象到epoll监听池中
}
void Accept::onDestroy(void){
	closeSocket();	// 关闭套接字
	// 修改epoll中的状态
}
void Accept::closeSocket(void){
	if( m_socket.fd != 0 ){
        close( m_socket.fd );
        m_socket.fd = 0;
    }
}

NS_HIVENET_END
