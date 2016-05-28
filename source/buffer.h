//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/28
// Time: 下午3:09
// To change this template use File | Settings | File Templates.
//

#ifndef __hivenet__buffer__
#define __hivenet__buffer__

#include "common.h"

NS_HIVENET_BEGIN

typedef std::vector<char> VectorChar;

class Buffer : public RefObject, public VectorChar
{
public:
	Buffer(void);
	virtual ~Buffer(void);

	int write(const void* ptr, int length, int offset);
	int read(void* ptr, int length, int offset);
	virtual inline std::string getClassName(void) const {
		return "Buffer";
	}
protected:

};// end class Buffer

NS_HIVENET_END

#endif
