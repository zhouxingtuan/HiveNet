//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/29
// Time: 上午9:08
// To change this template use File | Settings | File Templates.
//

#ifndef __hivenet__script__
#define __hivenet__script__

#include "handlerinterface.h"
#include "uniquemanager.h"
#include "epoll.h"

#include "lua.hpp"
#include "tolua++.h"

extern "C" {
#include "luasocket.h"
#include "mime.h"
#include "context.h"
#include "x509.h"
#include "ssl.h"
#include "luasql.h"
#include "luahiredis.h"
}

NS_HIVENET_BEGIN

#define UNIQUE_HANDLER_SCRIPT 2

class Script : public HandlerInterface, public EpollTaskFactory
{
public:
	friend class ScriptManager;
public:
    Script(unique_char uniqueType);
    virtual ~Script( void );

	static Unique* CreateFunction(unique_char uniqueType){
		return new Script(uniqueType);
	}

	// handler interface
	virtual bool onInitialize(void);
	virtual bool onDestroy(void);
	virtual bool onHandleMessage(unique_long handle, Packet* pPacket);
	virtual bool onUpdate(void);
	virtual bool onAcceptIn(unique_long handle);
	virtual bool onAcceptOut(unique_long handle);
	virtual bool onClientIn(unique_long handle);
	virtual bool onClientOut(unique_long handle);

	// epoll factory interface
	virtual TaskInterface* createAcceptIn(unique_long handle);
	virtual TaskInterface* createAcceptOut(unique_long handle);
	virtual TaskInterface* createClientIn(unique_long handle);
	virtual TaskInterface* createClientOut(unique_long handle);
	virtual TaskInterface* createPacketIn(unique_long handle, Packet* pPacket);

	virtual bool sendMessage(unique_long handle, const char* pData, unsigned int length){ return false; }
	virtual bool sendMessage(unique_long handle, Packet* pPacket);
	virtual void setState(lua_State* pState);
	inline lua_State * getState( void ) { return m_pState; }
    inline void setInitString(const char* initFile){ m_initString = initFile; }
    inline const std::string& getInitString(void) const { return m_initString; }
	inline bool executeFile( const char * script_file_path ){
		if( luaL_loadfile(m_pState, script_file_path ) == 0 ){
			if( lua_resume( m_pState, 0 ) == 0 ){
				return true;
			}
		}
		outputError();
		return false;
	}
	inline bool executeText( const char * script, const int script_length, const char * comment = NULL ){
		if( luaL_loadbuffer( m_pState, script, script_length, comment ) == 0 ){
			if( lua_pcall( m_pState, 0, 0, 0 ) == 0 ){
				return true;
			}
		}
		outputError();
		return false;
	}
    inline void luaCall( int parameter_number, int result_count = 0 ){
        if( lua_pcall( m_pState, parameter_number, result_count, 0 ) != 0 ){
            outputError();
        }
    }
	// 定制C++调用Lua的全局函数
	inline void callGlobalFunction(const char * function_name, unique_long handle, void* ptr, const char* class_name){
		lua_getglobal(m_pState, function_name);
		tolua_pushnumber(m_pState,(lua_Number)handle);
		tolua_pushusertype(m_pState, (void*)ptr, class_name);
		luaCall(2);
		lua_settop(m_pState, 0);
	}
	inline void callGlobalFunction(const char * function_name, void* ptr, const char* class_name){
		lua_getglobal(m_pState, function_name);
		tolua_pushusertype(m_pState, (void*)ptr, class_name);
		luaCall(1);
		lua_settop(m_pState, 0);
	}
	inline void callGlobalFunction(const char * function_name, unique_long handle){
		lua_getglobal(m_pState, function_name);
		tolua_pushnumber(m_pState,(lua_Number)handle);
		luaCall(1);
		lua_settop(m_pState, 0);
	}
    inline void callGlobalFunction(const char * function_name){
        lua_getglobal(m_pState, function_name);
        luaCall(0);
        lua_settop(m_pState, 0);
    }
    virtual inline std::string getClassName(void) const {
        return "Script";
    }
protected:
	// 保护函数，被ScriptManager调用
	inline void setMaster(Script* pMaster){
		SAFE_RELEASE(m_pMaster)
		m_pMaster = pMaster;
		SAFE_RETAIN(m_pMaster)
	}
	inline void outputError(void){
		const char* msg = lua_tostring( m_pState, -1 );
		if( msg == NULL )
			msg = "(error without message)";
		fprintf(stderr, "%s\n", msg);
	}
protected:
	lua_State* m_pState;
    Script* m_pMaster;
    std::string m_initString;
};//end class Script

DEFINE_TASK(TaskUpdate, Script, onUpdate)
DEFINE_TASK_LONG(TaskAcceptIn, Script, onAcceptIn, unique_long)
DEFINE_TASK_LONG(TaskAcceptOut, Script, onAcceptOut, unique_long)
DEFINE_TASK_LONG(TaskClientIn, Script, onClientIn, unique_long)
DEFINE_TASK_LONG(TaskClientOut, Script, onClientOut, unique_long)
DEFINE_TASK_PACKET(TaskHandleMessage, Script, onHandleMessage, unique_long, Packet)

NS_HIVENET_END

#endif
