//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/29
// Time: 下午5:00
// To change this template use File | Settings | File Templates.
//

#ifndef __hivenet__worker__
#define __hivenet__worker__

#include "handlerinterface.h"

NS_HIVENET_BEGIN

class HandlerQueue;

class Worker : public RefObject, public Thread
{
public:
	explicit Worker(HandlerQueue* pHandlerQueue);
    virtual ~Worker(void);
    virtual int threadFunction(void);

    virtual inline std::string getClassName(void) const {
        return "Worker";
    }
protected:
	HandlerQueue* m_pHandlerQueue;
};// end class Worker

NS_HIVENET_END

#endif
