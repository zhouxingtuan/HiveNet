//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/30
// Time: 下午9:47
// To change this template use File | Settings | File Templates.
//

#include "handlerinterface.h"
#include "handlerqueue.h"

NS_HIVENET_BEGIN

HandlerInterface::HandlerInterface(unique_char uniqueType) : Unique(uniqueType), Sync(), m_isInHandlerQueue(false) {

}
HandlerInterface::~HandlerInterface(void){
	releaseTask();
}
void HandlerInterface::releaseTask(void){
	this->lock();
	for( auto pTask : m_taskQueue ){
		pTask->release();
	}
	m_taskQueue.clear();
	this->unlock();
}
void HandlerInterface::doHandler(void){
	TaskInterface* pTask = NULL;
	bool doTaskFinished = false;
	bool releaseTaskAtEnd = false;
	this->lock();
	if( !m_taskQueue.empty() ){
		pTask = m_taskQueue.front();		// 这里获取第一个任务来执行
		pTask->retain();					// 在执行前需要自己保留引用(1)，因为别的线程很可能调用releaseTask
	}
	this->unlock();
	if( NULL != pTask ){
		doTaskFinished = pTask->doTask(); 	// 执行任务，因为已经保证handler被worker独占，所以可以不在临界区内
		pTask->release();					// 这次释放对应的是前面获取时保留的引用(1)
	}
	this->lock();
	// 任务有可能在一次执行中未结束，需要重新执行，检查doTaskFinished
	// 在上面执行的过程中，很可能被调用releaseTask清空了队列，这里执行反向检查
	if( doTaskFinished && !m_taskQueue.empty() && m_taskQueue.front() == pTask ){
		releaseTaskAtEnd = true;			// 在这里释放对象会占用大量临界区的时间，先标记，放到最后执行
		m_taskQueue.pop_front();			// 将前面执行的任务出队
	}
	if( m_taskQueue.empty() ){				// 执行结束之后，如果队列里面没有任务，那么不将handler重新提交
		m_isInHandlerQueue = false;
		this->unlock();
	}else{
		m_isInHandlerQueue = true;
		this->unlock();
		HandlerQueue::getInstance()->acceptHandler(this);	// 重新将handler提交给队列
	}
	if( releaseTaskAtEnd ){
		pTask->release();					// 执行结束才可以释放，对应的是进入队列时的retain
	}
}
void HandlerInterface::acceptTask(TaskInterface* pTask){
	pTask->retain();
	this->lock();
	m_taskQueue.push_back(pTask);
	if( m_isInHandlerQueue ){	// 已经在队列里面，入队后不做任何处理
		this->unlock();
	}else{						// 原先不在队列中则重新入队
		m_isInHandlerQueue = true;
		this->unlock();
		HandlerQueue::getInstance()->acceptHandler(this);	// 重新将handler提交给队列
	}
}
void HandlerInterface::acceptTaskSilence(TaskInterface* pTask){
	pTask->retain();
	this->lock();
	m_taskQueue.push_back(pTask);
	this->unlock();
}
void HandlerInterface::notifyHandlerQueue(void){
	this->lock();
	if( m_isInHandlerQueue ){	// 已经在队列里面，入队后不做任何处理
		this->unlock();
	}else{						// 原先不在队列中则重新入队
		if(m_taskQueue.empty()){
			this->unlock();
		}else{
			m_isInHandlerQueue = true;
			this->unlock();
			HandlerQueue::getInstance()->acceptHandler(this);	// 重新将handler提交给队列
		}
	}
}

NS_HIVENET_END
