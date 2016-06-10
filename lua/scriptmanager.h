//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/29
// Time: 上午9:11
// To change this template use File | Settings | File Templates.
//

#ifndef __hivenet__scriptmanager__
#define __hivenet__scriptmanager__

#include "script.h"

NS_HIVENET_BEGIN

class ScriptManager : public RefObject
{
public:
	typedef std::vector<Script*> ScriptVector;
	typedef std::vector<int> IntVector;
	ScriptManager(void);
	virtual ~ScriptManager(void);

	static ScriptManager* getInstance(void);
	static ScriptManager* createInstance(void);
	static void destroyInstance(void);

	void timerUpdate(void);
	bool startTimer(unsigned int second, unsigned int nsecond=0);
	virtual bool sendPacket(unique_long handle, Packet* pPacket);
	Script* create(void);			// 创建一个脚本
	void idle(unique_long handle);	// 闲置这个脚本by handle
	void idle(Script* pScript);		// 闲置这个脚本by ptr
	void remove(unique_long handle);	// 移除这个脚本by handle
	void remove(Script* pScript);		// 移除这个脚本by ptr
	Script* getScript(unique_long handle);
	Script* getMaster(){ return m_pMaster; }
	virtual inline std::string getClassName(void) const {
		return "ScriptManager";
	}
protected:
	void closeMaster(void);	//关闭当前的Lua状态机
	void openMaster(void);	//打开当前的Lua状态机
protected:
	Script* m_pMaster;
	timer_t m_timer_id;
};// end class ScriptManager
NS_HIVENET_END

#endif
