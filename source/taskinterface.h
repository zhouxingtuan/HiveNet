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
	virtual void doTask(void) = 0;		// 执行任务内容

	inline HandlerInterface* getHandler(void){ return m_pHandler; }
    virtual inline std::string getClassName(void) const {
        return "TaskInterface";
    }
protected:
	HandlerInterface* m_pHandler;
};// end class HandlerInterface

NS_HIVENET_END

#endif
