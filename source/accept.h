//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/31
// Time: 下午9:38
// To change this template use File | Settings | File Templates.
//

#ifndef __hivenet__accept__
#define __hivenet__accept__

#include "packet.h"

NS_HIVENET_BEGIN

#define PACKET_HEAD_LENGTH 4
#define MAX_LENGTH_NOT_IDENTIFY 64
#define MAX_LENGTH_IDENTIFY 67108870	// 67108864(64 M)
#define IP_SIZE 18
struct SocketInformation{
    int fd;
    char ip[IP_SIZE];//192.168.110.110
    unsigned short port;
};

enum SocketHandlerType {
	SOCKET_HANDLER_NULL = 0,
	SOCKET_HANDLER_ACCEPT = 1,
	SOCKET_HANDLER_CLIENT = 2,
};

class Epoll;

class Accept : public RefObject, public Sync
{
public:
	friend class Epoll;
	friend class AcceptManager;
	typedef std::deque<Packet*> PacketQueue;
public:
	explicit Accept(Epoll* pEpoll);
	virtual ~Accept(void);

	virtual void removeSocket(void);
	virtual inline void setSocket(const char* ip, unsigned short port){
		strcpy(m_socket.ip, ip);
		m_socket.port = port;
	}
	virtual inline void setSocketFD(int fd){ m_socket.fd = fd; }
	virtual inline int getSocketFD(void) const { return m_socket.fd; }
	inline void setIdentify(bool identify){ m_isIdentify = identify; }
	inline bool isIdentify(void) const { return m_isIdentify; }
	inline int getMaxLength(void) const {
		if(isIdentify()){
			return MAX_LENGTH_IDENTIFY;
		}else{
			return MAX_LENGTH_NOT_IDENTIFY;
		}
	}
	inline SocketHandlerType getSocketHandlerType(void) const { return m_handlerType; }
    inline bool triggerStateOutFlag(void) { return !m_stateOutFlag.test_and_set(); }
    inline void clearStateOutFlag(void) { m_stateOutFlag.clear(); }
	inline unsigned short getIndex(void) const { return m_uniqueHandle.getIndex(); }
	inline unsigned short getVersion(void) const { return m_uniqueHandle.getVersion(); }
	inline unsigned int getHandle(void) const { return m_uniqueHandle.getHandle(); }
    virtual inline std::string getClassName(void) const {
        return "Accept";
    }
protected:
	virtual bool tryReadSocket(void);
	virtual bool tryWriteSocket(void);
	virtual bool readSocket(void);
	virtual bool writeSocket(Packet* pPacket);
	virtual void resetData(void);
	virtual void closeSocket(void);
	// 保护函数，被ScriptManager调用
	inline void increaseVersion(void){ m_uniqueHandle.increase(); }
	inline void setIndex(unsigned short index){ m_uniqueHandle.setIndex(index); }
	void dispatchPacket(Packet* pPacket);
	void receivePacket(Packet* pPacket);
	void releasePacket(void);
protected:
	SocketInformation m_socket;
	PacketQueue m_packetQueue;
	Epoll* m_pEpoll;
	Packet* m_tempReadPacket;
	UniqueHandle m_uniqueHandle;
	std::atomic_flag m_stateOutFlag;
	SocketHandlerType m_handlerType;
	volatile bool m_isIdentify;
};//end class Accept

NS_HIVENET_END

#endif
