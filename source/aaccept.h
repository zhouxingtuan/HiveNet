//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/31
// Time: 下午9:38
// To change this template use File | Settings | File Templates.
//

#ifndef __hivenet__accept__
#define __hivenet__accept__

#include "handlerinterface.h"

NS_HIVENET_BEGIN

#define IP_SIZE 18
struct SocketInformation{
    int fd;
    char ip[IP_SIZE];//192.168.110.110
    unsigned short port;
};

class Epoll;

class Accept : public HandlerInterface
{
public:
	explicit Accept(Epoll* pEpoll);
	virtual ~Accept(void);

	virtual void onInitialize(void);
	virtual void onDestroy(void);
	virtual void readSocket(void);
	virtual void writeSocket(void);

	virtual inline void setSocket(const char* ip, unsigned short port){
		strcpy(m_socket.ip, ip);
		m_socket.port = port;
	}
	virtual inline void setSocketFD(int fd){ m_socket.fd = fd; }
	virtual inline int getSocketFD(void) const { return m_socket.fd; }
	inline void setIdentify(bool identify){ m_isIdentify = identify; }
	inline bool isIdentify(void) const { return m_isIdentify; }
	inline unsigned short getIndex(void) const { return m_uniqueHandle.getIndex(); }
	inline unsigned short getVersion(void) const { return m_uniqueHandle.getVersion(); }
	inline unsigned int getHandle(void) const { return m_uniqueHandle.getHandle(); }
    virtual inline std::string getClassName(void) const {
        return "Accept";
    }
protected:
	void closeSocket(void);
	// 保护函数，被ScriptManager调用
	inline void increaseVersion(void){ m_uniqueHandle.increase(); }
	inline void setIndex(unsigned short index){ m_uniqueHandle.setIndex(index); }
protected:
	SocketInformation m_socket;
	Epoll* m_pEpoll;
	Packet* m_tempReadPacket;
	Packet* m_tempWritePacket;
	UniqueHandle m_uniqueHandle;
	volatile bool m_isIdentify;
};//end class Accept

DEFINE_TASK(TaskReadSocket, Accept, readSocket)
DEFINE_TASK(TaskWriteSocket, Accept, writeSocket)

NS_HIVENET_END

#endif
