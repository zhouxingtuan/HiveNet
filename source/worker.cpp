//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/29
// Time: 下午5:01
// To change this template use File | Settings | File Templates.
//

#include "worker.h"
#include "taskqueue.h"

NS_HIVENET_BEGIN

Worker::Worker(TaskQueue* pTaskQueue) : RefObject(), Thread(), m_pTaskQueue(pTaskQueue) {

}
Worker::~Worker(void){

}
int Worker::threadFunction(void){
	TaskInterface* pTask;
	while(true){
		m_pTaskQueue->lock();
		pTask = m_pTaskQueue->nextTask();		// 临界区
		while(NULL == pTask){
			m_pTaskQueue->wait();
			pTask = m_pTaskQueue->nextTask();	// 临界区: task在进入队列的时候已经retain过了，所以这里直接使用
		};
		m_pTaskQueue->unlock();
		pTask->doTask();	// 执行任务内容
		pTask->release();	// 执行完之后释放掉
	};
	return 0;
}

NS_HIVENET_END
