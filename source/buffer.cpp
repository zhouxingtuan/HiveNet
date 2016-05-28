//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/28
// Time: 下午3:09
// To change this template use File | Settings | File Templates.
//

#include "buffer.h"

NS_HIVENET_BEGIN

Buffer::Buffer(void) : RefObject(), VectorChar() {

}
Buffer::~Buffer(void){

}

int Buffer::write(const void* ptr, int length, int offset){
	int needSize = offset + length;
	if( (int)this->size() < needSize ){
		this->resize(needSize, 0);
	}
	char* writeTo = (char*)(this->data()) + offset;
	memcpy(writeTo, ptr, length);
	return length;
}
int Buffer::read(void* ptr, int length, int offset){
	int needSize = offset + length;
	if( (int)this->size() < needSize){
		return 0;
	}
	char* readFrom = (char*)(this->data()) + offset;
	memcpy(ptr, readFrom, length);
	return length;
}

NS_HIVENET_END
