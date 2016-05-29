//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/29
// Time: 上午9:16
// To change this template use File | Settings | File Templates.
//

#ifndef __hivenet__handlerinterface__
#define __hivenet__handlerinterface__

#include "packet.h"

NS_HIVENET_BEGIN

class HandlerInterface : public RefObject
{
public:
	HandlerInterface(void) : RefObject(){}
	virtual ~HandlerInterface(void){}

	virtual void onInitialize(void) = 0;
	virtual void onHandleMessage(Packet* pPacket) = 0;
	virtual void onUpdate(void) = 0;
	virtual void onDestroy(void) = 0;

    virtual inline std::string getClassName(void) const {
        return "HandlerInterface";
    }
protected:

};// end class HandlerInterface

NS_HIVENET_END

#endif
