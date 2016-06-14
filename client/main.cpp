//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/6/5
// Time: 下午4:00
// To change this template use File | Settings | File Templates.
//

#include "client.h"

USING_NS_HIVENET;

class ClientNotify : public ClientInterface
{
public:
	ClientNotify(void) : ClientInterface(){}
	virtual ~ClientNotify(void){}

	virtual void notifyConnectServerFailed(Client* pClient){
		fprintf(stderr, "Client called notifyConnectServerFailed\n");
	}
	virtual void notifyConnectServerSuccess(Client* pClient){
		fprintf(stderr, "Client called notifyConnectServerSuccess\n");
	}
	virtual void notifyConnectOut(Client* pClient){
		fprintf(stderr, "Client called notifyConnectOut\n");
	}
	virtual void notifyPacketIn(Client* pClient, Packet* pPacket){
		fprintf(stderr, "Client called notifyPacketIn\n");
	}
};

int main(int argc, char *argv[])
{
	fprintf(stderr, "hello world!\n");

	ClientNotify* pNotify = new ClientNotify();
	Client* pClient = new Client();
	pClient->retain();

	char ipstringbuffer[46];
	struct sockaddr_in  *sockaddr_ipv4;
    struct sockaddr_in6 *sockaddr_ipv6;
	struct addrinfo hints;
	struct addrinfo *res = NULL;
	struct addrinfo *ptr = NULL;
	int result;
	int i = 1;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
//	hints.ai_flags = AI_DEFAULT;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_socktype = SOCK_STREAM;
	result = getaddrinfo("cocospider.com", NULL, &hints, &res);
	if(result == -1){
		fprintf(stderr, "getaddrinfo result error\n");
		goto MAIN_EXIT;
	}
	for(ptr = res; ptr != NULL; ptr = ptr->ai_next){
		fprintf(stderr, "getaddrinfo response %d\n", i++);
		fprintf(stderr, "\tFlags: 0x%x\n", ptr->ai_flags);
		fprintf(stderr, "\tFamily: ");
		switch(ptr->ai_family){
			case AF_UNSPEC:
				fprintf(stderr, "Unspecified\n");
				break;
			case AF_INET:
				fprintf(stderr, "AF_INET (IPv4)\n");
				sockaddr_ipv4 = (struct sockaddr_in *) ptr->ai_addr;
				fprintf(stderr, "\tIPv4 address %s\n", inet_ntoa(sockaddr_ipv4->sin_addr) );
				break;
			case AF_INET6:
				fprintf(stderr, "AF_INET6 (IPv6)\n");
				sockaddr_ipv6 = (struct sockaddr_in6 *) ptr->ai_addr;
				fprintf(stderr, "\tIPv6 address %s\n", inet_ntop(AF_INET6, &sockaddr_ipv6->sin6_addr, ipstringbuffer, 46) );
				break;
			default:
				fprintf(stderr, "Other %ld\n", ptr->ai_family);
				break;
		};
	}
	freeaddrinfo(res);	// 记得释放

	pClient->setNotifyInterface(pNotify);
	pClient->setSocket("127.0.0.1", 8888);
	pClient->startThread();		// 这个函数开启新的线程建立连接

	while(true){
		sleep(1);
		// 这个函数需要在主循环中调用，用来分发事件；这样就确保调用线程安全
		pClient->dispatchEvent();
	};

	sleep(5);
MAIN_EXIT:
	pClient->release();
	delete pNotify;
	return 0;
}

