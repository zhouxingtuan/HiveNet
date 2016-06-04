//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/31
// Time: 下午10:12
// To change this template use File | Settings | File Templates.
//

#ifndef __hivenet__epoll__
#define __hivenet__epoll__

#include "handlerinterface.h"
#include "accept.h"
#include "client.h"

NS_HIVENET_BEGIN

class Epoll;
class EpollTaskFactory
{
public:
	EpollTaskFactory(void){}
	virtual ~EpollTaskFactory(void){}

	virtual TaskInterface* createAcceptIn(unsigned int handle, Epoll* pEpoll) = 0;
	virtual TaskInterface* createAcceptOut(unsigned int handle, Epoll* pEpoll) = 0;
	virtual TaskInterface* createClientIn(unsigned int handle, Epoll* pEpoll) = 0;
	virtual TaskInterface* createClientOut(unsigned int handle, Epoll* pEpoll) = 0;
	virtual TaskInterface* createPacketIn(unsigned int handle, Epoll* pEpoll, Packet* pPacket) = 0;
	virtual TaskInterface* createPacketOut(unsigned int handle, Epoll* pEpoll, Packet* pPacket) = 0;
};// end class

#define MAX_LISTEN_SIZE 11008
#define MAX_EPOLL_EVENT 64
#define EPOLL_WAIT_FLAG -1

/*--------------------------------------------------------------------*/
inline int setNonBlocking(int fd){
    if(fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0)|O_NONBLOCK) == -1){
  		return -1;
    }
    return 0;
}
inline int epollAdd(int epollfd, int fd, void* ptr, unsigned int events=EPOLLIN){
	struct epoll_event ev;
	ev.events = events;
    ev.data.ptr = ptr;
    return epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}
inline int epollRemove(int epollfd, int fd){
    return epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
}
//read state is the default state;
inline int epollChange(int epollfd, int fd, void* ptr, unsigned int events=EPOLLIN){
	struct epoll_event ev;
	ev.events = events;
    ev.data.ptr = ptr;
	return epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}
/*--------------------------------------------------------------------*/
class Epoll : public HandlerInterface
{
public:
	Epoll(void);
	virtual ~Epoll(void);

	static Epoll* getInstance(void);
	static Epoll* createInstance(void);
	static void destroyInstance(void);

	virtual void onInitialize(void);
	virtual void onDestroy(void);
	virtual void onUpdate(void);

	virtual bool sendPacket(unsigned int handle, Packet* pPacket);
	virtual unsigned int createClient(const char* ip, unsigned short port);
	virtual void closeClient(unsigned int handle);
	virtual void closeAccept(unsigned int handle);
	virtual inline void setListenSocket(const char* ip, unsigned short port){
		strcpy(m_socket.ip, ip);
    	m_socket.port = port;
	}
    virtual inline std::string getClassName(void) const {
        return "Epoll";
    }
protected:
	bool initListenSocket(void);
	void closeListenSocket(void);
	bool createEpoll(void);
	bool waitEpoll(void);
protected:
	volatile int m_curfds;
	int m_epollfd;
	struct epoll_event m_events[MAX_EPOLL_EVENT];
	SocketInformation m_socket;

};// end class Epoll

NS_HIVENET_END

#endif
