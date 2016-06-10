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
#include "uniquemanager.h"

NS_HIVENET_BEGIN
/*--------------------------------------------------------------------*/
class Epoll;
class EpollTaskFactory
{
public:
	EpollTaskFactory(void){}
	virtual ~EpollTaskFactory(void){}

	virtual TaskInterface* createAcceptIn(unique_long handle) = 0;
	virtual TaskInterface* createAcceptOut(unique_long handle) = 0;
	virtual TaskInterface* createClientIn(unique_long handle) = 0;
	virtual TaskInterface* createClientOut(unique_long handle) = 0;
	virtual TaskInterface* createPacketIn(unique_long handle, Packet* pPacket) = 0;
};// end class EpollTaskFactory
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
class Epoll : public RefObject
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

	virtual bool initialize(void);
	virtual bool update(void);

	virtual bool sendPacket(unique_long handle, Packet* pPacket);
	virtual void setIdentify(unique_long handle, bool identify);
	virtual EpollTaskFactory* getFactory(void){ return m_pFactory; }
	virtual void setFactory(EpollTaskFactory* pFactory){ m_pFactory = pFactory; }
	virtual unique_long createClient(const char* ip, unsigned short port);
	virtual void closeClient(unique_long handle);
	virtual bool acceptSocket(void);
	virtual void closeAccept(unique_long handle);
	virtual inline void setListenSocket(const char* ip, unsigned short port){
		strcpy(m_socket.ip, ip);
    	m_socket.port = port;
	}
	virtual void closeEpoll(void);
    virtual inline std::string getClassName(void) const {
        return "Epoll";
    }
protected:
	virtual inline void setEpollExit(bool exitNow){ m_exitNow = true; }
	virtual inline bool isEpollExit(void) const { return m_exitNow; }
	virtual bool tryRemoveSocket(Accept* pAccept);
	bool receiveClient(Client* pClient);
	bool receivePacket(unique_long handle, Packet* pPacket);
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
	inline Accept* createAccept(void){
		Accept* pAccept = (Accept*)UniqueManager::getInstance()->create(UNIQUE_HANDLER_ACCEPT);
		pAccept->setEpoll(this);
		return pAccept;
	}
	inline Accept* getAccept(unique_long handle){
		Unique* pUnique = UniqueManager::getInstance()->getByHandle(handle);
		if( NULL == pUnique ){
			return NULL;
		}
		if( pUnique->getType() != UNIQUE_HANDLER_ACCEPT ){
			return NULL;
		}
		return (Accept*)pUnique;
	}
	inline Client* createClient(void){
		Client* pClient = (Client*)UniqueManager::getInstance()->create(UNIQUE_HANDLER_CLIENT);
		pClient->setEpoll(this);
		return pClient;
	}
	inline Client* getClient(unique_long handle){
		Unique* pUnique = UniqueManager::getInstance()->getByHandle(handle);
		if( NULL == pUnique ){
			return NULL;
		}
		if( pUnique->getType() != UNIQUE_HANDLER_CLIENT ){
			return NULL;
		}
		return (Client*)pUnique;
	}
	inline void idleConnect(Accept* pAccept){
		UniqueManager::getInstance()->idle(pAccept);
	}
protected:
	EpollTaskFactory* m_pFactory;
	volatile int m_curfds;
	int m_epollfd;
	volatile bool m_exitNow;
	struct epoll_event m_events[MAX_EPOLL_EVENT];
	SocketInformation m_socket;
};// end class Epoll

NS_HIVENET_END

#endif
