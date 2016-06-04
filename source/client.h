//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/31
// Time: 下午9:40
// To change this template use File | Settings | File Templates.
//

#ifndef __hivenet__client__
#define __hivenet__client__

#include "accept.h"

NS_HIVENET_BEGIN

class Client : public Accept
{
public:
	explicit Client(Epoll* pEpoll);
	virtual ~Client(void);

	virtual bool onInitialize(void);

    virtual inline std::string getClassName(void) const {
        return "Client";
    }
protected:
	virtual bool connectServer(void);
};

NS_HIVENET_END

#endif
