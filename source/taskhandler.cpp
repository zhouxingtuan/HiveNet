//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/29
// Time: 下午9:44
// To change this template use File | Settings | File Templates.
//

#include "taskhandler.h"

NS_HIVENET_BEGIN

void TaskInitialize::doTask(void){
	getHandler()->onInitialize();
}

void TaskUpdate::doTask(void){
	getHandler()->onUpdate();
}

void TaskDestroy::doTask(void){
	getHandler()->onDestroy();
}

void TaskHandleMessage::doTask(void){
	getHandler()->onHandleMessage(m_pPacket);
}

NS_HIVENET_END
