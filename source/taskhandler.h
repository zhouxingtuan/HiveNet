//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/29
// Time: 下午9:43
// To change this template use File | Settings | File Templates.
//

#ifndef __hivenet__taskhandler__
#define __hivenet__taskhandler__

#include "taskinterface.h"
#include "handlerinterface.h"

NS_HIVENET_BEGIN

class TaskInitialize : public TaskInterface
{
public:
	explicit TaskInitialize(HandlerInterface* pHandler) : TaskInterface(pHandler){}
	virtual ~TaskInitialize(void){}
	virtual void doTask(void);
    virtual inline std::string getClassName(void) const {
        return "TaskInitialize";
    }
};// end class TaskInitialize

class TaskUpdate : public TaskInterface
{
public:
	explicit TaskUpdate(HandlerInterface* pHandler) : TaskInterface(pHandler){}
	virtual ~TaskUpdate(void){}
	virtual void doTask(void);
    virtual inline std::string getClassName(void) const {
        return "TaskUpdate";
    }
};// end class TaskUpdate

class TaskDestroy : public TaskInterface
{
public:
	explicit TaskDestroy(HandlerInterface* pHandler) : TaskInterface(pHandler){}
	virtual ~TaskDestroy(void){}
	virtual void doTask(void);
    virtual inline std::string getClassName(void) const {
        return "TaskDestroy";
    }
};// end class TaskDestroy

class TaskHandleMessage : public TaskInterface
{
public:
	explicit TaskHandleMessage(HandlerInterface* pHandler, Packet* pPacket)
		: TaskInterface(pHandler), m_pPacket(pPacket){
		m_pPacket->retain();
	}
	virtual ~TaskHandleMessage(void){ m_pPacket->release(); }
	virtual void doTask(void);
	Packet* getPacket(void){ return m_pPacket; }
    virtual inline std::string getClassName(void) const {
        return "TaskHandleMessage";
    }
protected:
	Packet* m_pPacket;
};// end class TaskHandleMessage



NS_HIVENET_END

#endif
