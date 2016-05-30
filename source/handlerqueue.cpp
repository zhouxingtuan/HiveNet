//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/30
// Time: 下午9:16
// To change this template use File | Settings | File Templates.
//

#include "handlerqueue.h"

NS_HIVENET_BEGIN

static HandlerQueue* g_pHandlerQueue = NULL;
HandlerQueue::HandlerQueue() : RefObject(), Sync() {
	pthread_cond_init(&m_cond, NULL);
}
HandlerQueue::~HandlerQueue(){
	for( auto pWorker : m_workers ){
		pWorker->cancelThread();
		pWorker->release();
	}
	m_workers.clear();
	this->lock();
	for( auto pHandler : m_queue ){
		pHandler->release();
	}
	m_queue.clear();
	this->unlock();
	pthread_cond_destroy(&m_cond);
}
HandlerQueue* HandlerQueue::getInstance(void){
	return g_pHandlerQueue;
}
HandlerQueue* HandlerQueue::createInstance(void){
	if(g_pHandlerQueue == NULL){
		g_pHandlerQueue = new HandlerQueue();
		SAFE_RETAIN(g_pHandlerQueue)
	}
	return g_pHandlerQueue;
}
void HandlerQueue::destroyInstance(void){
    SAFE_RELEASE(g_pHandlerQueue)
}

void HandlerQueue::createWorker(int workerNumber){
	if( m_workers.size() > 0 ){
		return;
	}
	for(int i=0; i<workerNumber; ++i){
		Worker* pWorker = new Worker(this);
		m_workers.push_back(pWorker);
		pWorker->startThread();
	}
}
void HandlerQueue::acceptHandler(HandlerInterface* pHandler){
	pHandler->retain();
	this->lock();
	m_queue.push_back(pHandler);
	this->signal();	// wake up workers
	this->unlock();
}
HandlerInterface* HandlerQueue::nextHandler(void){
	HandlerInterface* pHandler;
	if( m_queue.empty() ){
		return NULL;
	}else{
		pHandler = m_queue.front();
		m_queue.pop_front();
	}
	return pHandler;
}

NS_HIVENET_END
