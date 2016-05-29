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
	ScriptManager(void);
	virtual ~ScriptManager(void);

	static ScriptManager* getInstance(void);
	static ScriptManager* createInstance(void);
	static void destroyInstance(void);

	Script* create(void);
	void remove(int stateID);
	void remove(Script* pScript);
	Script* getScript(int stateID);
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
	ScriptVector m_scripts;
	Script* m_pMaster;
};// end class ScriptManager
NS_HIVENET_END

#endif
