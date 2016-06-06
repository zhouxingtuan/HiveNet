//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/29
// Time: 下午5:01
// To change this template use File | Settings | File Templates.
//

#include "worker.h"
#include "handlerqueue.h"

NS_HIVENET_BEGIN

Worker::Worker(HandlerQueue* pHandlerQueue) : RefObject(), Thread(), m_pHandlerQueue(pHandlerQueue) {

}
Worker::~Worker(void){

}
int Worker::threadFunction(void){
	HandlerInterface* pHandler;
	m_pHandlerQueue->retain();
	this->retain();
	while(true){
		m_pHandlerQueue->lock();
		pHandler = m_pHandlerQueue->nextHandler();		// 临界区
		while(NULL == pHandler){
			m_pHandlerQueue->wait();
			pHandler = m_pHandlerQueue->nextHandler();	// 临界区: Handler在进入队列的时候已经retain过了，所以这里直接使用
			// 注解：因为HandlerQueue是一个全局的队列，基本不会去释放队列中的Handler对象，所有在处理Handler时不需要重新引用
		};
		m_pHandlerQueue->unlock();
		pHandler->doHandler();	// 执行任务内容
		pHandler->release();	// 执行完之后释放掉，对应的是入队时的retain
	};
	this->release();
	m_pHandlerQueue->release();
	return 0;
}

NS_HIVENET_END
