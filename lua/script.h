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

#include "lua.hpp"
#include "tolua++.h"

extern "C" {
#include "luasocket.h"
#include "mime.h"
#include "context.h"
#include "x509.h"
#include "ssl.h"
#include "luasql.h"
}

NS_HIVENET_BEGIN

class Script : public HandlerInterface
{
public:
	friend class ScriptManager;
public:
    explicit Script(lua_State* pState=NULL);
    virtual ~Script( void );

	// interface
	virtual bool onInitialize(void);
	virtual bool onDestroy(void);
	virtual bool onHandleMessage(Packet* pPacket);
	virtual bool onUpdate(void);

    inline void setInitString(const char* initFile){ m_initString = initFile; }
    inline const std::string& getInitString(void) const { return m_initString; }
	inline lua_State * getState( void ) { return m_pState; }
	inline UniqueHandle getUniqueHandle(void) const { return m_uniqueHandle; }
	inline unsigned short getIndex(void) const { return m_uniqueHandle.getIndex(); }
	inline unsigned short getVersion(void) const { return m_uniqueHandle.getVersion(); }
	inline unsigned int getHandle(void) const { return m_uniqueHandle.getHandle(); }
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
	inline void callGlobalFunction(const char * function_name, void* ptr, const char* class_name){
		lua_getglobal( m_pState, function_name );
		tolua_pushusertype(m_pState, (void*)ptr, class_name);
		luaCall(1);
		lua_settop(m_pState, 0);
	}
    inline void callGlobalFunction(const char * function_name){
        lua_getglobal( m_pState, function_name );
        luaCall(0);
        lua_settop(m_pState, 0);
    }
    virtual inline std::string getClassName(void) const {
        return "Script";
    }
protected:
	// 保护函数，被ScriptManager调用
	inline void increaseVersion(void){ m_uniqueHandle.increase(); }
	inline void setIndex(unsigned short index){ m_uniqueHandle.setIndex(index); }
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
    UniqueHandle m_uniqueHandle;
    std::string m_initString;
};//end class Script

DEFINE_TASK(TaskUpdate, Script, onUpdate)
DEFINE_TASK_PARAM(TaskHandleMessage, Script, onHandleMessage, Packet)

NS_HIVENET_END

#endif
