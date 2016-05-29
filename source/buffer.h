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

typedef std::vector<char> CharVector;

class Buffer : public RefObject, public CharVector
{
public:
	Buffer(void);
	virtual ~Buffer(void);

	inline int write(const void* ptr, int length, int offset){
		int needSize = offset + length;
		if( (int)this->size() < needSize ){
			this->resize(needSize, 0);
		}
		char* writeTo = (char*)(this->data()) + offset;
		memcpy(writeTo, ptr, length);
		return length;
	}
	inline int read(void* ptr, int length, int offset){
		int needSize = offset + length;
		if( (int)this->size() < needSize){
			return 0;
		}
		char* readFrom = (char*)(this->data()) + offset;
		memcpy(ptr, readFrom, length);
		return length;
	}
	virtual inline std::string getClassName(void) const {
		return "Buffer";
	}
protected:

};// end class Buffer

NS_HIVENET_END

#endif
