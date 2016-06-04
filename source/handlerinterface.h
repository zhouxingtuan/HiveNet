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
	virtual void onDestroy(void) = 0;

	virtual void releaseTask(void);		// 放弃掉所有任务
    virtual inline std::string getClassName(void) const {
        return "HandlerInterface";
    }
protected:
    void doHandler(void);						// Worker 调用执行任务检测
    void acceptTask(TaskInterface* pTask);		// TaskInterface 调用接收任务
protected:
	bool m_isInHandlerQueue;			// 标记当前主体对象是否已经在队列中等待Worker处理
	TaskInterfaceQueue m_taskQueue;		// 当前主体对象需要完成的任务队列，确保任务独占主体的资源
};// end class HandlerInterface

DEFINE_TASK(TaskInitialize, HandlerInterface, onInitialize)
DEFINE_TASK(TaskDestroy, HandlerInterface, onDestroy)

//class TaskInitialize : public TaskInterface
//{
//public:
//	explicit TaskInitialize(HandlerInterface* pHandler) : TaskInterface(pHandler){}
//	virtual ~TaskInitialize(void){}
//	virtual void doTask(void){
//		getHandler()->onInitialize();
//	}
//    virtual inline std::string getClassName(void) const {
//        return "TaskInitialize";
//    }
//};// end class TaskInitialize
//
//class TaskDestroy : public TaskInterface
//{
//public:
//	explicit TaskDestroy(HandlerInterface* pHandler) : TaskInterface(pHandler){}
//	virtual ~TaskDestroy(void){}
//	virtual void doTask(void){
//		getHandler()->onDestroy();
//	}
//    virtual inline std::string getClassName(void) const {
//        return "TaskDestroy";
//    }
//};// end class TaskDestroy

NS_HIVENET_END

#endif
