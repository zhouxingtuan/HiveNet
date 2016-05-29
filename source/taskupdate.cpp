//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/29
// Time: 下午9:44
// To change this template use File | Settings | File Templates.
//

#include "taskupdate.h"

NS_HIVENET_BEGIN

TaskUpdate::TaskUpdate(HandlerInterface* pHandler) : m_pHandler(pHandler) {
	m_pHandler->retain();
}
TaskUpdate::~TaskUpdate(void){
	m_pHandler->release();
}

void TaskUpdate::doTask(void){
	m_pHandler->onUpdate();
}

NS_HIVENET_END
