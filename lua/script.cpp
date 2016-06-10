//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/29
// Time: 上午9:10
// To change this template use File | Settings | File Templates.
//

#include "script.h"
#include "manual.hpp"

NS_HIVENET_BEGIN

Script::Script(unique_char uniqueType) : HandlerInterface(uniqueType), m_pState(NULL), m_pMaster(NULL){

}
Script::~Script(void){
	if(NULL != m_pState){
		lua_close(m_pState); // 先关闭自己
	}
    SAFE_RELEASE(m_pMaster)  // 释放掉master的占用
}
void Script::setState(lua_State* pState){
	if(pState==NULL){
		m_pState = luaL_newstate();
		lua_pop( m_pState, luaopen_base( m_pState ) );
		lua_pop( m_pState, luaopen_math( m_pState ) );
		lua_pop( m_pState, 1 );
		// Save a pointer to the thread Manager object in the global table
		// using the new thread script vm pointer as a key.
		lua_pushlightuserdata( m_pState, m_pState );
		lua_pushlightuserdata( m_pState, this );
		lua_settable( m_pState, LUA_GLOBALSINDEX );
	}else{
		m_pState = pState;
	}
	// open standard libs
	luaL_openlibs( m_pState );
	lua_settop( m_pState, 0 );
	// open lua socket libs
	luaopen_socket_core(m_pState);
	luaopen_mime_core(m_pState);
	luaopen_ssl_context(m_pState);
	luaopen_ssl_x509(m_pState);
	luaopen_ssl_core(m_pState);
	// open luasql libs
	luaopen_luasql_mysql(m_pState);
	// open luahiredis libs
	luaopen_hiredis(m_pState);
	// open self define c libs
	tolua_hivenet_open(m_pState);
}
bool Script::onInitialize(void){
	static char onInitialize[]="onInitialize";
	// 初始化加载Lua代码文件
	executeText( m_initString.c_str(), m_initString.length() );
	// 初始化调用 onInitialize 函数，会回传当前Script的指针，这个指针在Lua生命周期内都是有效的
	callGlobalFunction(onInitialize, this, getClassName().c_str());
	return true;
}
bool Script::onHandleMessage(unique_long handle, Packet* pPacket){
	static char onHandleMessage[]="onHandleMessage";
	static char namePacket[]="Packet";
	callGlobalFunction(onHandleMessage, handle, pPacket, namePacket);
	return true;
}
bool Script::onUpdate(void){
	static char onUpdate[]="onUpdate";
	callGlobalFunction( onUpdate );
	return true;
}
bool Script::onDestroy(void){
    static char onDestroy[]="onDestroy";
    callGlobalFunction( onDestroy );
    UniqueManager::getInstance()->idle(this);	// 这里比较特别，在idle一个对象的时候，需要先调用onDestroy在移除
    return true;
}
bool Script::onAcceptIn(unique_long handle){
    static char onAcceptIn[]="onAcceptIn";
    callGlobalFunction( onAcceptIn, handle );
    return true;
}
bool Script::onAcceptOut(unique_long handle){
    static char onAcceptOut[]="onAcceptOut";
    callGlobalFunction( onAcceptOut, handle );
    return true;
}
bool Script::onClientIn(unique_long handle){
    static char onClientIn[]="onClientIn";
    callGlobalFunction( onClientIn, handle );
    return true;
}
bool Script::onClientOut(unique_long handle){
    static char onClientOut[]="onClientOut";
    callGlobalFunction( onClientOut, handle );
    return true;
}
TaskInterface* Script::createAcceptIn(unique_long handle){
	return new TaskAcceptIn(this, handle);
}
TaskInterface* Script::createAcceptOut(unique_long handle){
	return new TaskAcceptOut(this, handle);
}
TaskInterface* Script::createClientIn(unique_long handle){
	return new TaskClientIn(this, handle);
}
TaskInterface* Script::createClientOut(unique_long handle){
	return new TaskClientOut(this, handle);
}
TaskInterface* Script::createPacketIn(unique_long handle, Packet* pPacket){
	return new TaskHandleMessage(this, handle, pPacket);
}
bool Script::sendMessage(unique_long handle, Packet* pPacket){
	UniqueHandle h = handle;
	unique_char t = h.getType();
	switch(t){
		case UNIQUE_HANDLER_ACCEPT:
		case UNIQUE_HANDLER_CLIENT:{
			return Epoll::getInstance()->sendPacket(handle, pPacket);
			break;
		}
		case UNIQUE_HANDLER_SCRIPT:{
			return ScriptManager::getInstance()->sendPacket(handle, pPacket);
			break;
		}
		default:{
			fprintf(stderr, "--Script::sendMessage handler type is not valid\n");
			break;
		}
	}
	return false;
}

NS_HIVENET_END
