//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/28
// Time: 下午12:54
// To change this template use File | Settings | File Templates.
//

#include "common.h"

NS_HIVENET_BEGIN

/*--------------------------------------------------------------------*/
bool Thread::startThread(void){
	cancelThread();
	if( pthread_create(&m_pThread,NULL,staticThreadFunction,this) ){
		return false;
	}
	pthread_detach(m_pThread);
	return true;
}
void* Thread::staticThreadFunction(void* pData){
	Thread* ret = (Thread*)pData;
	return (void*)ret->threadFunction();
}
void Thread::cancelThread(void){
	if(m_pThread != 0 ){
		pthread_cancel( m_pThread );
		m_pThread = 0;
	}
}
/*--------------------------------------------------------------------*/

NS_HIVENET_END
