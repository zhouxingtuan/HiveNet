//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/28
// Time: 下午2:58
// To change this template use File | Settings | File Templates.
//

#include "packet.h"

NS_HIVENET_BEGIN

Packet::Packet(int bufferSize) : RefObject(),m_pBuffer(NULL),m_cursor(0) {
	assert(bufferSize > 0 && "Packet new bufferSize should be > 0");
	m_pBuffer = new Buffer();	// 是否处理分配内存失败？
	m_pBuffer->retain();
	m_pBuffer->reserve(bufferSize);
}
Packet::Packet(Buffer* pBuffer) : RefObject(),m_pBuffer(pBuffer),m_cursor(0) {
	assert(pBuffer != NULL && "Packet new pBuffer should not be NULL");
	pBuffer->retain();
}
Packet::~Packet(void){
	SAFE_RELEASE(m_pBuffer)
}


NS_HIVENET_END
