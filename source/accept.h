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

#define UNIQUE_HANDLER_ACCEPT 0
#define UNIQUE_HANDLER_CLIENT 1

class Epoll;

class Accept : public Unique, public Sync
{
public:
	friend class Epoll;
	typedef std::deque<Packet*> PacketQueue;
public:
	explicit Accept(unique_char uniqueType);
	virtual ~Accept(void);

	static Unique* CreateFunction(unique_char uniqueType){
		return new Accept(uniqueType);
	}

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
	inline void setEpoll(Epoll* pEpoll){ m_pEpoll = pEpoll; }
	inline Epoll* getEpoll(void) { return m_pEpoll; }
    inline bool triggerStateOutFlag(void) { return !m_stateOutFlag.test_and_set(); }
    inline void clearStateOutFlag(void) { m_stateOutFlag.clear(); }
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
	void dispatchPacket(Packet* pPacket);
	void receivePacket(Packet* pPacket);
	void releasePacket(void);
protected:
	SocketInformation m_socket;
	PacketQueue m_packetQueue;
	Epoll* m_pEpoll;
	Packet* m_tempReadPacket;
	std::atomic_flag m_stateOutFlag;
	volatile bool m_isIdentify;
};//end class Accept

NS_HIVENET_END

#endif
