//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/29
// Time: 下午9:43
// To change this template use File | Settings | File Templates.
//

#ifndef __hivenet__taskupdate__
#define __hivenet__taskupdate__

#include "taskinterface.h"
#include "handlerinterface.h"

NS_HIVENET_BEGIN

class TaskUpdate : public TaskInterface
{
public:
	explicit TaskUpdate(HandlerInterface* pHandler);
	virtual ~TaskUpdate(void);

	virtual void doTask(void);

    virtual inline std::string getClassName(void) const {
        return "TaskUpdate";
    }
protected:
	HandlerInterface* m_pHandler;
};// end class TaskUpdate

NS_HIVENET_END

#endif
