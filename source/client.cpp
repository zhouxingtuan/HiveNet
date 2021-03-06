//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/31
// Time: 下午9:41
// To change this template use File | Settings | File Templates.
//

#include "client.h"
#include "epoll.h"

NS_HIVENET_BEGIN

Client::Client(unique_char uniqueType) : Accept(uniqueType) {
	setIdentify(true);	// 自己建立的连接无限制
}
Client::~Client(void){

}
void* Client::syncConnectServer(void* pData){
	Client* ret = (Client*)pData;
	if( ret->tryConnectServer() ){
		return 0;
	}
	return 0;
}
bool Client::tryConnectServer(void){
	if( connectServer() ){
		if( m_pEpoll->receiveClient(this) ){
			return true;
		}
	}
	removeSocket();
	return false;
}
bool Client::connectServer(void){
    int fd;
    struct sockaddr_in servaddr;
    socklen_t socklen = sizeof(struct sockaddr_in);
    bzero(&servaddr, socklen);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr( m_socket.ip );//htonl(INADDR_ANY);
    servaddr.sin_port = htons( m_socket.port );

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1){
        return false;
    }
    if( connect(fd, (struct sockaddr *)&servaddr, socklen) == -1 ){
        close( fd );
        return false;
    }
    m_socket.fd = fd;
    return true;
}

NS_HIVENET_END
