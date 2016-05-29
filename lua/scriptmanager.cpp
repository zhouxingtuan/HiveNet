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
	unsigned int index;
    Script* ret;
    lock();
    if( !m_idleIndex.empty() ){
    	index = m_idleIndex.back();
    	m_idleIndex.pop_back();
		ret = m_scripts[index];
		if( NULL == ret ){
			ret = new Script(NULL);
			ret->retain();
			ret->setMaster(m_pMaster);
			ret->setIndex(index);
			m_scripts[index] = ret;
		}//else{
//			ret->increaseVersion();	// 这里对这个对象进行了重复使用
		//}
    }else{
    	index = m_scripts.size();
    	ret = new Script(NULL);
		ret->retain();
		ret->setMaster(m_pMaster);
		ret->setIndex(index);
		m_scripts.push_back(ret);
    }
    unlock();
	return ret;
}
void ScriptManager::idle(unsigned int handle){
	Script* ret = NULL;
	UniqueHandle h(handle);
	unsigned short index = h.getIndex();
	lock();
	if( index < m_scripts.size() ){
		ret = m_scripts[index];
		if( NULL != ret ){
			ret->increaseVersion();	// 这里对这个对象进行了重复使用
			m_idleIndex.push_back(index);
		}
    }
	unlock();
}
void ScriptManager::idle(Script* pScript){
	idle( pScript->getHandle() );
}
void ScriptManager::remove(unsigned int handle){
	Script* ret = NULL;
	UniqueHandle h(handle);
	unsigned short index = h.getIndex();
    lock();
    if( index < m_scripts.size() ){
		ret = m_scripts[index];
		m_scripts[index] = NULL;
		if( NULL != ret ){
			m_idleIndex.push_back(index);
		}
    }
	unlock();
	if( NULL != ret ){
		ret->release();
	}
}
void ScriptManager::remove(Script* script){
    remove( script->getHandle() );
}
Script* ScriptManager::getScript(unsigned int handle){
    Script* ret = NULL;
    UniqueHandle h(handle);
	unsigned short index = h.getIndex();
	lock();
	if( index < m_scripts.size() ){
		ret = m_scripts[index];
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
