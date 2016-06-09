//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/29
// Time: 上午9:12
// To change this template use File | Settings | File Templates.
//

#include "scriptmanager.h"

NS_HIVENET_BEGIN

static ScriptManager* g_pScriptManager = NULL;
ScriptManager::ScriptManager() : RefObject(), m_pMaster(NULL) {
	openMaster();
}
ScriptManager::~ScriptManager(){
	closeMaster();
}
ScriptManager* ScriptManager::getInstance(void){
	return g_pScriptManager;
}
ScriptManager* ScriptManager::createInstance(void){
	if(g_pScriptManager == NULL){
		g_pScriptManager = new ScriptManager();
		SAFE_RETAIN(g_pScriptManager)
	}
	return g_pScriptManager;
}
void ScriptManager::destroyInstance(void){
    SAFE_RELEASE(g_pScriptManager)
}
//创建一个Script
Script* ScriptManager::create(void){
	Script* pScript = (Script*)UniqueManager::getInstance()->create(UNIQUE_HANDLER_SCRIPT);
	if( NULL == pScript->getState() ){
		pScript->setMaster(m_pMaster);
		pScript->setState(NULL);
	}
	return pScript;
}
void ScriptManager::idle(unique_long handle){
	UniqueManager::getInstance()->idle(handle);
}
void ScriptManager::idle(Script* pScript){
	idle( pScript->getHandle() );
}
void ScriptManager::remove(unique_long handle){
	UniqueManager::getInstance()->remove(handle);
}
void ScriptManager::remove(Script* script){
    remove( script->getHandle() );
}
Script* ScriptManager::getScript(unique_long handle){
    return (Script*)UniqueManager::getInstance()->getByHandle(handle);
}
//打开当前的Lua状态机
void ScriptManager::openMaster(void){
	if( m_pMaster == NULL ){
		lua_State* state = lua_open();
		if( state ){
			m_pMaster = (Script*)UniqueManager::getInstance()->create(UNIQUE_HANDLER_SCRIPT);
			m_pMaster->setState(state);
			m_pMaster->retain();
		}
	}
}
//关闭当前的Lua状态机
void ScriptManager::closeMaster(void){
	if(m_pMaster != NULL) {
		// 移除所有该类型的script对象
		UniqueManager::getInstance()->removeByType(UNIQUE_HANDLER_SCRIPT);
//		UniqueManager::getInstance()->remove(m_pMaster);
		m_pMaster->release();
		m_pMaster = NULL;
	}
}

NS_HIVENET_END
