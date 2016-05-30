//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/30
// Time: 下午9:16
// To change this template use File | Settings | File Templates.
//

#ifndef __hivenet__handlerqueue__
#define __hivenet__handlerqueue__

#include "handlerinterface.h"
#include "worker.h"

NS_HIVENET_BEGIN

class HandlerQueue : public RefObject, public Sync
{
public:
	friend class Worker;
	friend class HandlerInterface;
public:
	typedef std::deque<HandlerInterface*> HandlerInterfaceQueue;
	typedef std::vector<Worker*> WorkerVector;
	HandlerQueue(void);
	virtual ~HandlerQueue(void);

	static HandlerQueue* getInstance(void);
	static HandlerQueue* createInstance(void);
	static void destroyInstance(void);

	void createWorker(int workerNumber);

	inline void signal(void){
		pthread_cond_signal(&m_cond);
	}
	inline void wait(void){
		pthread_cond_wait(&m_cond, &m_mutex);
	}
    virtual inline std::string getClassName(void) const {
        return "HandlerQueue";
    }
protected:
	void acceptHandler(HandlerInterface* pHandler);		// HandlerInterface 调用
	HandlerInterface* nextHandler(void);				// Worker 调用
protected:
	pthread_cond_t m_cond;
	HandlerInterfaceQueue m_queue;
	WorkerVector m_workers;
};

NS_HIVENET_END

#endif
