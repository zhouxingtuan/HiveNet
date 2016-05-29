//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/29
// Time: 下午8:35
// To change this template use File | Settings | File Templates.
//

#ifndef __hivenet__taskqueue__
#define __hivenet__taskqueue__

#include "taskinterface.h"
#include "worker.h"

NS_HIVENET_BEGIN

class TaskQueue : public RefObject, public Sync
{
public:
	typedef std::deque<TaskInterface*> TaskInterfaceQueue;
	typedef std::vector<Worker*> WorkerVector;
	TaskQueue(void);
	virtual ~TaskQueue(void);

	static TaskQueue* getInstance(void);
	static TaskQueue* createInstance(void);
	static void destroyInstance(void);

	void createWorker(int workerNumber);
	void acceptTask(TaskInterface* pTask);
	TaskInterface* nextTask(void);

	inline void signal(void){
		pthread_cond_signal(&m_cond);
	}
	inline void wait(void){
		pthread_cond_wait(&m_cond, &m_mutex);
	}
    virtual inline std::string getClassName(void) const {
        return "TaskQueue";
    }
protected:
	pthread_cond_t m_cond;
	TaskInterfaceQueue m_queue;
	WorkerVector m_workers;
};// end class TaskQueue

NS_HIVENET_END

#endif
