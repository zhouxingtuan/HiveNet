//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/6/5
// Time: 下午3:59
// To change this template use File | Settings | File Templates.
//

#ifndef __hivenet__client__
#define __hivenet__client__

//#define NS_HIVENET_BEGIN namespace hivenet {
//#define NS_HIVENET_END };
//#define USING_NS_HIVENET using namespace hivenet;
#define NS_HIVENET_BEGIN
#define NS_HIVENET_END
#define USING_NS_HIVENET

//c libs
#include <assert.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>  //atof函数
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <limits.h>
#include <inttypes.h>

//std libs
#include <atomic>
#include <thread>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>

//socket & net libs
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>		/* basic system data types */
#include <sys/socket.h>		/* basic socket definitions */
#include <netinet/in.h>		/* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>		/* inet(3) functions */
#include <fcntl.h>			/* nonblocking */

//thread libs
#include <pthread.h>
#include <semaphore.h>

#define SAFE_DELETE(ptr) if(ptr != NULL){ delete ptr; ptr = NULL; }
#define SAFE_DELETE_ARRAY(ptr) if(ptr != NULL){ delete [] ptr; ptr = NULL; }
#define SAFE_RETAIN(ptr) if(ptr != NULL){ ptr->retain(); }
#define SAFE_RELEASE(ptr) if(ptr != NULL){ ptr->release(); ptr = NULL; }

NS_HIVENET_BEGIN

/*--------------------------------------------------------------------*/
// 拥有同步互斥量的类
class Sync
{
public:
	Sync(void){
		pthread_mutex_init(&m_mutex, NULL);
	}
	virtual ~Sync(void){
		pthread_mutex_destroy(&m_mutex);
	}
	inline void lock(void){
		pthread_mutex_lock(&m_mutex);
	}
	inline void rlock(void){
		pthread_mutex_lock(&m_mutex);
	}
	inline void unlock(void){
		pthread_mutex_unlock(&m_mutex);
	}
	virtual inline std::string getClassName(void) const {
		return "Sync";
	}
protected:
	pthread_mutex_t m_mutex;
};
/*--------------------------------------------------------------------*/
// 引用计数基类
class RefObject
{
public:
	RefObject(void) : m_referenceCount(0){}
	virtual ~RefObject(void){}
	inline void release(void){
		if( std::atomic_fetch_sub_explicit(&m_referenceCount, 1, std::memory_order_relaxed) == 1 ){
			delete this;
		}
	}
	inline void retain(void){
		std::atomic_fetch_add_explicit(&m_referenceCount, 1, std::memory_order_relaxed);
	}
	inline int getRefCount(void){ return (int)m_referenceCount; }
	virtual inline std::string getClassName(void) const {
		return "RefObject";
	}
protected:
	std::atomic<int> m_referenceCount;
};
/*--------------------------------------------------------------------*/
// 线程基类
class Thread
{
public:
	typedef void*(*ThreadCallback)(void* pData);
public:
	Thread(void) : m_pThread(0){}
	virtual ~Thread(void){}
	bool startThread(void);
	void cancelThread(void);
	virtual int threadFunction(void) = 0;

	static pthread_t staticThread(ThreadCallback start_rtn, void *arg);

	virtual inline std::string getClassName(void) const {
		return "Thread";
	}
private:
	static void* staticThreadFunction(void* pData);
protected:
	pthread_t m_pThread;
};
/*--------------------------------------------------------------------*/
typedef std::vector<char> CharVector;

class Buffer : public RefObject, public CharVector
{
public:
	Buffer(void) : RefObject(), CharVector(){}
	virtual ~Buffer(void){}

	inline int write(const void* ptr, int length, int offset){
		int needSize = offset + length;
		if( (int)this->size() < needSize ){
			this->resize(needSize, 0);
		}
		char* writeTo = (char*)(this->data()) + offset;
		memcpy(writeTo, ptr, length);
		return length;
	}
	inline int read(void* ptr, int length, int offset){
		int needSize = offset + length;
		if( (int)this->size() < needSize){
			return 0;
		}
		char* readFrom = (char*)(this->data()) + offset;
		memcpy(ptr, readFrom, length);
		return length;
	}
	virtual inline std::string getClassName(void) const {
		return "Buffer";
	}
protected:

};// end class Buffer
/*--------------------------------------------------------------------*/
enum PacketReadWriteState {
	PACKET_READ_WRITE = 0,
	PACKET_READ_ONLY = 1,
	PACKET_WRITE_ONLY = 2,
};

class Packet : public RefObject
{
public:
    explicit Packet(int bufferSize);
    explicit Packet(Buffer* pBuffer);
    virtual ~Packet(void);

	inline bool isReadEnable(void) const { return PACKET_WRITE_ONLY != m_rwState; }
	inline bool isWriteEnable(void) const { return PACKET_READ_ONLY != m_rwState; }
	inline void setReadWriteState(PacketReadWriteState state){ m_rwState = state; }
	inline void setCursor(int cur){ m_cursor = cur; }
	inline void moveCursor(int length){ m_cursor += length; }
	inline int getCursor(void) const { return m_cursor; }
	inline void resetCursor(void){ m_cursor = 0; }
	inline Buffer* getBuffer(void){ return m_pBuffer; }
	inline char* getCursorPtr(void){ return m_pBuffer->data() + m_cursor; }
	inline int getLength(void) const { return (int)m_pBuffer->size(); }
	inline bool isCursorEnd(void) const { return getCursor() >= getLength(); }
	inline int write(const void* ptr, int length){
		if( !isWriteEnable() ){
			return 0;
		}
		int n = m_pBuffer->write(ptr, length, getCursor());
		if( n > 0 ){
			moveCursor(n);
		}
		return n;
	}
	inline int read(void* ptr, int length){
		if( !isReadEnable() ){
			return false;
		}
		int n = m_pBuffer->read(ptr, length, getCursor());
		if( n > 0 ){
			moveCursor(n);
		}
		return n;
	}
	virtual inline std::string getClassName(void) const {
		return "Packet";
	}
protected:
	Buffer* m_pBuffer;		// 数据指针
	int m_cursor;			// 数据读取的偏移
	PacketReadWriteState m_rwState;		// 是不是只读状态
};// end class Packet
/*--------------------------------------------------------------------*/
#define CLIENT_SELECT_FLAG 5000
#define PACKET_HEAD_LENGTH 4
#define IP_SIZE 18
struct SocketInformation{
    int fd;
    char ip[IP_SIZE];//192.168.110.110
    unsigned short port;
};
class Client;
class ClientInterface
{
public:
	ClientInterface(void){}
	virtual ~ClientInterface(void){}

	virtual void notifyConnectServerFailed(Client* pClient) = 0;
	virtual void notifyConnectServerSuccess(Client* pClient) = 0;
	virtual void notifyConnectOut(Client* pClient) = 0;
	virtual void notifyPacketIn(Client* pClient, Packet* pPacket) = 0;
};// end class ClientInterface

class Client : public RefObject, public Sync, public Thread
{
public:
	typedef std::deque<Packet*> PacketQueue;
public:
	Client(void);
	virtual ~Client(void);
	virtual int threadFunction(void);

	virtual bool receivePacket(Packet* pPacket);
	virtual void removeSocket(void);
	virtual void setNotifyInterface(ClientInterface* pInterface){ m_pInterface = pInterface; }
	virtual inline void setSocket(const char* ip, unsigned short port){
		strcpy(m_socket.ip, ip);
		m_socket.port = port;
	}
	virtual inline void setSocketFD(int fd){ m_socket.fd = fd; }
	virtual inline int getSocketFD(void) const { return m_socket.fd; }
    virtual inline std::string getClassName(void) const {
        return "Client";
    }
protected:
	virtual bool connectServer(void);
	virtual bool tryReadSocket(void);
	virtual bool tryWriteSocket(void);
	virtual bool readSocket(void);
	virtual bool writeSocket(Packet* pPacket);
	virtual void closeSocket(void);
	void dispatchPacket(Packet* pPacket);
	void releasePacket(void);
protected:
	SocketInformation m_socket;
	PacketQueue m_packetQueue;
	Packet* m_tempReadPacket;
	ClientInterface* m_pInterface;
};//end class Client
/*--------------------------------------------------------------------*/

NS_HIVENET_END

#endif
