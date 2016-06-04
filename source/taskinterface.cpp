//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/30
// Time: 下午10:28
// To change this template use File | Settings | File Templates.
//

#include "taskinterface.h"
#include "handlerinterface.h"

NS_HIVENET_BEGIN

TaskInterface::TaskInterface(HandlerInterface* pHandler) : RefObject(), m_pHandler(pHandler) {
	m_pHandler->retain();
}
TaskInterface::~TaskInterface(void){
	m_pHandler->release();
}
void TaskInterface::commitTask(void){
	m_pHandler->acceptTask(this);
}
void TaskInterface::commitTaskSilence(void){
	m_pHandler->acceptTaskSilence(this);
}

NS_HIVENET_END
