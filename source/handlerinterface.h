//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/29
// Time: 上午9:16
// To change this template use File | Settings | File Templates.
//

#ifndef __hivenet__handlerinterface__
#define __hivenet__handlerinterface__

#include "taskinterface.h"
#include "packet.h"

NS_HIVENET_BEGIN

class HandlerInterface : public RefObject, public Sync
{
public:
	friend class Worker;
	friend class TaskInterface;
public:
	typedef std::deque<TaskInterface*> TaskInterfaceQueue;
	HandlerInterface(void);
	virtual ~HandlerInterface(void);

	virtual void onInitialize(void) = 0;
	virtual void onHandleMessage(Packet* pPacket) = 0;
	virtual void onUpdate(void) = 0;
	virtual void onDestroy(void) = 0;

    virtual inline std::string getClassName(void) const {
        return "HandlerInterface";
    }
protected:
    void doHandler(void);						// Worker 调用执行任务检测
    void acceptTask(TaskInterface* pTask);		// TaskInterface 调用接收任务
protected:
	bool m_isInHandlerQueue;
	TaskInterfaceQueue m_taskQueue;
};// end class HandlerInterface

NS_HIVENET_END

#endif
