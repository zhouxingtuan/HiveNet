//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/29
// Time: 下午8:36
// To change this template use File | Settings | File Templates.
//

#include "taskqueue.h"

NS_HIVENET_BEGIN

static TaskQueue* g_pTaskQueue = NULL;
TaskQueue::TaskQueue() : RefObject(), Sync() {
	pthread_cond_init(&m_cond, NULL);
}
TaskQueue::~TaskQueue(){
	for( auto pWorker : m_workers ){
		pWorker->cancelThread();
		pWorker->release();
	}
	m_workers.clear();
	this->lock();
	for( auto pTask : m_queue ){
		pTask->release();
	}
	m_queue.clear();
	this->unlock();
	pthread_cond_destroy(&m_cond);
}
TaskQueue* TaskQueue::getInstance(void){
	return g_pTaskQueue;
}
TaskQueue* TaskQueue::createInstance(void){
	if(g_pTaskQueue == NULL){
		g_pTaskQueue = new TaskQueue();
		SAFE_RETAIN(g_pTaskQueue)
	}
	return g_pTaskQueue;
}
void TaskQueue::destroyInstance(void){
    SAFE_RELEASE(g_pTaskQueue)
}

void TaskQueue::createWorker(int workerNumber){
	if( m_workers.size() > 0 ){
		return;
	}
	for(int i=0; i<workerNumber; ++i){
		Worker* pWorker = new Worker(this);
		m_workers.push_back(pWorker);
		pWorker->startThread();
	}
}
void TaskQueue::acceptTask(TaskInterface* pTask){
	pTask->retain();
	this->lock();
	m_queue.push_back(pTask);
	this->signal();	// wake up workers
	this->unlock();
}
TaskInterface* TaskQueue::nextTask(void){
	TaskInterface* pTask;
	if( m_queue.empty() ){
		return NULL;
	}else{
		pTask = m_queue.front();
		m_queue.pop_front();
	}
	return pTask;
}

NS_HIVENET_END
