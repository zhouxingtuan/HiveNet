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
/*--------------------------------------------------------------------*/
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
};// end class EpollTaskFactory
/*--------------------------------------------------------------------*/
class AcceptManager : public RefObject, public Sync
{
public:
	typedef std::vector<Accept*> AcceptVector;
	typedef std::vector<int> IntVector;
public:
	AcceptManager(void);
	virtual ~AcceptManager(void);

	Accept* createAccept(Epoll* pEpoll);
	Client* createClient(Epoll* pEpoll);
	void idle(Accept* pAccept);
	Accept* getByHandle(unsigned int handle);
protected:
	void releaseData(void);
protected:
	AcceptVector m_accepts;
	IntVector m_idleIndex;
};// end class AcceptManager
/*--------------------------------------------------------------------*/
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
	friend class Accept;
	friend class Client;
public:
	Epoll(void);
	virtual ~Epoll(void);

	static Epoll* getInstance(void);
	static Epoll* createInstance(void);
	static void destroyInstance(void);

	virtual bool onInitialize(void);
	virtual bool onDestroy(void);
	virtual bool onUpdate(void);

	virtual bool sendAcceptPacket(unsigned int handle, Packet* pPacket);
	virtual bool sendClientPacket(unsigned int handle, Packet* pPacket);
	virtual EpollTaskFactory* getFactory(void){ return m_pFactory; }
	virtual void setFactory(EpollTaskFactory* pFactory){ m_pFactory = pFactory; }
	virtual unsigned int createClient(const char* ip, unsigned short port);
	virtual void closeClient(unsigned int handle);
	virtual bool acceptSocket(void);
	virtual void closeAccept(unsigned int handle);
	virtual inline void setListenSocket(const char* ip, unsigned short port){
		strcpy(m_socket.ip, ip);
    	m_socket.port = port;
	}
    virtual inline std::string getClassName(void) const {
        return "Epoll";
    }
protected:
	virtual bool onRemoveSocket(Accept* pAccept);
	bool receiveClient(Client* pClient);
	bool receivePacket(unsigned int handle, Packet* pPacket);
	inline void changeStateOut(Accept* pAccept){
		if( pAccept->triggerStateOutFlag() ){
			if( epollChange(m_epollfd, pAccept->getSocketFD(), pAccept, EPOLLIN | EPOLLOUT) < 0 ){
				pAccept->clearStateOutFlag();    /// 如果当前修改失败，下次还得重来
			}
		}
	}
	inline void changeStateIn(Accept* pAccept){
		epollChange(m_epollfd,  pAccept->getSocketFD(), pAccept, EPOLLIN);
		pAccept->clearStateOutFlag();
	}
	inline void changeStateRemove(Accept* pAccept){
		epollRemove(m_epollfd, pAccept->getSocketFD());
	}
	bool initListenSocket(void);
	void closeListenSocket(void);
	bool createEpoll(void);
	bool waitEpoll(void);
protected:
	EpollTaskFactory* m_pFactory;
	AcceptManager* m_pAccepts;
	AcceptManager* m_pClients;
	volatile int m_curfds;
	int m_epollfd;
	struct epoll_event m_events[MAX_EPOLL_EVENT];
	SocketInformation m_socket;
};// end class Epoll

//DEFINE_TASK_PARAM(TaskRemoveSocket, Epoll, onRemoveSocket, Accept)

NS_HIVENET_END

#endif
