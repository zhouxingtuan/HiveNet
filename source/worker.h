//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/29
// Time: 下午5:00
// To change this template use File | Settings | File Templates.
//

#ifndef __hivenet__worker__
#define __hivenet__worker__

#include "taskinterface.h"

NS_HIVENET_BEGIN

class TaskQueue;

class Worker : public RefObject, public Thread
{
public:
	explicit Worker(TaskQueue* pTaskQueue);
    virtual ~Worker(void);
    virtual int threadFunction(void);

    virtual inline std::string getClassName(void) const {
        return "Worker";
    }
protected:
	TaskQueue* m_pTaskQueue;
};// end class Worker

NS_HIVENET_END

#endif
