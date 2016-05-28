//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/28
// Time: 下午12:53
// To change this template use File | Settings | File Templates.
//

#ifndef __hivenet__common__
#define __hivenet__common__

#define NS_HIVENET_BEGIN namespace hivenet {
#define NS_HIVENET_END };
#define USING_NS_HIVENET using namespace hivenet;

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
#include <sys/signal.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/time.h>

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

//epoll & net libs
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>		/* basic system data types */
#include <sys/socket.h>		/* basic socket definitions */
#include <netinet/in.h>		/* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>		/* inet(3) functions */
#include <sys/epoll.h>		/* epoll function */
#include <fcntl.h>			/* nonblocking */

//thread libs
#include <pthread.h>
#include <semaphore.h>

//jemalloc
#define JEMALLOC_NO_DEMANGLE
#include "jemalloc.h"

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
	Thread(void) : m_pThread(0){}
	virtual ~Thread(void){}
	bool startThread(void);
	virtual int threadFunction(void) = 0;
	virtual inline std::string getClassName(void) const {
		return "Thread";
	}
protected:
	void cancelThread(void);
private:
	static void* staticThreadFunction(void* pData);
protected:
	pthread_t m_pThread;
};
/*--------------------------------------------------------------------*/

NS_HIVENET_END

#endif
