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
ScriptManager::ScriptManager() : RefObject(), Sync(), m_pMaster(NULL) {
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
	int stateID;
    Script* ret = new Script(NULL);
    ret->retain();
    ret->setMaster(m_pMaster);
    lock();
    stateID = m_scripts.size();
    ret->setStateID(stateID);
	m_scripts.push_back(ret);
    unlock();
	return ret;
}
void ScriptManager::remove(int stateID){
	Script* ret = NULL;
    lock();
    if( stateID < (int)m_scripts.size() ){
		ret = m_scripts[stateID];
		m_scripts[stateID] = NULL;
    }
	unlock();
	if( NULL != ret ){
		ret->release();
	}
}
void ScriptManager::remove(Script* script){
    remove( script->getStateID() );
}
Script* ScriptManager::getScript(int stateID){
    Script* ret = NULL;
	lock();
	if( stateID < (int)m_scripts.size() ){
		ret = m_scripts[stateID];
	}
	unlock();
	return ret;
}
//打开当前的Lua状态机
void ScriptManager::openMaster(void){
	if( m_pMaster == NULL ){
		lua_State* state = lua_open();
		if( state ){
			m_pMaster = new Script(state);
			m_pMaster->retain();
		}
	}
}
//关闭当前的Lua状态机
void ScriptManager::closeMaster(void){
	//关闭脚本
    lock();
    for( auto pScript : m_scripts ){
    	if( NULL != pScript ){
    		pScript->release();
    	}
    }
	m_scripts.clear();
	//关闭状态
	if(m_pMaster != NULL) {
		m_pMaster->release();
		m_pMaster = NULL;
	}
	unlock();
}

NS_HIVENET_END
