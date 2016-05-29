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

class TaskInterface : public RefObject
{
public:
	TaskInterface(void) : RefObject(){}
	virtual ~TaskInterface(void){}

	virtual void doTask(void) = 0;

    virtual inline std::string getClassName(void) const {
        return "TaskInterface";
    }
protected:

};// end class HandlerInterface

NS_HIVENET_END

#endif
