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

#define DEFINE_TASK_PARAM(_NAME_, _HANDLER_, _FUNCTION_, _PARAM_)\
class _NAME_ : public TaskInterface\
{\
public:\
	explicit _NAME_(_HANDLER_* pHandler, _PARAM_* p##_PARAM_)\
		: TaskInterface(pHandler), m_p##_PARAM_(p##_PARAM_){\
		SAFE_RETAIN(m_p##_PARAM_)\
	}\
	virtual ~_NAME_(void){ SAFE_RELEASE(m_p##_PARAM_); }\
	virtual bool doTask(void){\
		return ((_HANDLER_*)getHandler())->_FUNCTION_(m_p##_PARAM_);\
	}\
protected:\
	_PARAM_* m_p##_PARAM_;\
};

NS_HIVENET_END

#endif
