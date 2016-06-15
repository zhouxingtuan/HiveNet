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

	pClient->setNotifyInterface(pNotify);
	pClient->setSocket("127.0.0.1", 8888);
	pClient->startThread();		// 这个函数开启新的线程建立连接

	while(true){
		sleep(1);
		// 这个函数需要在主循环中调用，用来分发事件；这样就确保调用线程安全
		pClient->dispatchEvent();
	};

	sleep(5);

	pClient->release();
	delete pNotify;
	return 0;
}

