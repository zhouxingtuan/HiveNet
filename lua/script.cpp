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

Script::Script(lua_State* pState) : HandlerInterface(), m_pState(NULL), m_pMaster(NULL){
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
		// 如果是新创建的，那么获取并记录master
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
	// open self define c libs
	tolua_hivenet_open(m_pState);
}
Script::~Script(void){
    lua_close(m_pState); // 先关闭自己
    SAFE_RELEASE(m_pMaster)  // 释放掉master的占用
}
bool Script::onInitialize(void){
	static char onInitialize[]="onInitialize";
	// 初始化加载Lua代码文件
	executeText( m_initString.c_str(), m_initString.length() );
	// 初始化调用 onInitialize 函数，会回传当前Script的指针，这个指针在Lua生命周期内都是有效的
	callGlobalFunction(onInitialize, this, getClassName().c_str());
	return true;
}
bool Script::onHandleMessage(Packet* pPacket){
	static char onHandleMessage[]="onHandleMessage";
	static char namePacket[]="Packet";
	callGlobalFunction(onHandleMessage, pPacket, namePacket);
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
    return true;
}


NS_HIVENET_END
