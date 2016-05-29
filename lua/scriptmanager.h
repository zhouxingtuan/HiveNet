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

class ScriptManager : public RefObject, public Sync
{
public:
	typedef std::vector<Script*> ScriptVector;
	typedef std::vector<int> IntVector;
	ScriptManager(void);
	virtual ~ScriptManager(void);

	static ScriptManager* getInstance(void);
	static ScriptManager* createInstance(void);
	static void destroyInstance(void);

	Script* create(void);			// 创建一个脚本
	void idle(unsigned int handle);	// 闲置这个脚本by handle
	void idle(Script* pScript);		// 闲置这个脚本by ptr
	void remove(unsigned int handle);	// 移除这个脚本by handle
	void remove(Script* pScript);		// 移除这个脚本by ptr
	Script* getScript(unsigned int handle);
	Script* getMaster(){ return m_pMaster; }
	virtual inline std::string getClassName(void) const {
		return "ScriptManager";
	}
protected:
	//关闭当前的Lua状态机
	void closeMaster(void);
	//打开当前的Lua状态机
	void openMaster(void);
protected:
	Script* m_pMaster;
	ScriptVector m_scripts;
	IntVector m_idleIndex;
};// end class ScriptManager
NS_HIVENET_END

#endif
