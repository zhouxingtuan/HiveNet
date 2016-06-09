//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/29
// Time: 下午8:34
// To change this template use File | Settings | File Templates.
//

#ifndef __hivenet__taskinterface__
#define __hivenet__taskinterface__

#include "common.h"

NS_HIVENET_BEGIN

class HandlerInterface;

class TaskInterface : public RefObject
{
public:
	explicit TaskInterface(HandlerInterface* pHandler);
	virtual ~TaskInterface(void);

	virtual void commitTask(void);		// 提交任务到流水线中
	virtual void commitTaskSilence(void);	// 只提交任务，不激活
	virtual bool doTask(void) = 0;		// 执行任务内容

	inline HandlerInterface* getHandler(void){ return m_pHandler; }
    virtual inline std::string getClassName(void) const {
        return "TaskInterface";
    }
protected:
	HandlerInterface* m_pHandler;
};// end class HandlerInterface

#define DEFINE_TASK(_NAME_, _HANDLER_, _FUNCTION_)\
class _NAME_ : public TaskInterface\
{\
public:\
	explicit _NAME_(_HANDLER_* pHandler) : TaskInterface(pHandler){}\
	virtual ~_NAME_(void){}\
	virtual bool doTask(void){\
		return ((_HANDLER_*)getHandler())->_FUNCTION_();\
	}\
};

#define DEFINE_TASK_LONG(_NAME_, _HANDLER_, _FUNCTION_, _LONG_)\
class _NAME_ : public TaskInterface\
{\
public:\
	explicit _NAME_(_HANDLER_* pHandler, _LONG_ num)\
		: TaskInterface(pHandler), m_##_LONG_(num){\
	}\
	virtual ~_NAME_(void){ }\
	virtual bool doTask(void){\
		return ((_HANDLER_*)getHandler())->_FUNCTION_(m_##_LONG_);\
	}\
protected:\
	_LONG_ m_##_LONG_;\
};

#define DEFINE_TASK_PACKET(_NAME_, _HANDLER_, _FUNCTION_, _LONG_, _PACKET_)\
class _NAME_ : public TaskInterface\
{\
public:\
	explicit _NAME_(_HANDLER_* pHandler, _LONG_ num, _PACKET_* ptr)\
		: TaskInterface(pHandler), m_##_LONG_(num), m_p##_PACKET_(ptr){\
		SAFE_RETAIN(m_p##_PACKET_)\
	}\
	virtual ~_NAME_(void){ SAFE_RELEASE(m_p##_PACKET_); }\
	virtual bool doTask(void){\
		return ((_HANDLER_*)getHandler())->_FUNCTION_(m_##_LONG_, m_p##_PACKET_);\
	}\
protected:\
	_LONG_ m_##_LONG_;\
	_PACKET_* m_p##_PACKET_;\
};

NS_HIVENET_END

#endif
