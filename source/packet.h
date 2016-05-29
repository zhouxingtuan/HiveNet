//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/28
// Time: 下午2:57
// To change this template use File | Settings | File Templates.
//

#ifndef __hivenet__packet__
#define __hivenet__packet__

#include "buffer.h"

NS_HIVENET_BEGIN

enum PacketReadWriteState {
	PACKET_READ_WRITE = 0,
	PACKET_READ_ONLY = 1,
	PACKET_WRITE_ONLY = 2,
};

class Packet : public RefObject
{
public:
    explicit Packet(int bufferSize);
    explicit Packet(Buffer* pBuffer);
    virtual ~Packet(void);

	inline bool isReadEnable(void) const { return PACKET_WRITE_ONLY != m_rwState; }
	inline bool isWriteEnable(void) const { return PACKET_READ_ONLY != m_rwState; }
	inline void setReadWriteState(PacketReadWriteState state){ m_rwState = state; }
	inline void moveCursor(int length){ m_cursor += length; }
	inline int getCursor(void) const { return m_cursor; }
	inline void resetCursor(void){ m_cursor = 0; }
	inline Buffer* getBuffer(void){ return m_pBuffer; }

	inline int write(const void* ptr, int length){
		if( !isWriteEnable() ){
			return 0;
		}
		int n = m_pBuffer->write(ptr, length, getCursor());
		if( n > 0 ){
			moveCursor(n);
		}
		return n;
	}
	inline int read(void* ptr, int length){
		if( !isReadEnable() ){
			return false;
		}
		int n = m_pBuffer->read(ptr, length, getCursor());
		if( n > 0 ){
			moveCursor(n);
		}
		return n;
	}
	virtual inline std::string getClassName(void) const {
		return "Packet";
	}
protected:
	Buffer* m_pBuffer;		// 数据指针
	int m_cursor;			// 数据读取的偏移
	PacketReadWriteState m_rwState;		// 是不是只读状态
};// end class Packet

NS_HIVENET_END

#endif
