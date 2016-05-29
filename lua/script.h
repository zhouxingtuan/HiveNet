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
}

NS_HIVENET_BEGIN

class Script : public HandlerInterface
{
	friend class ScriptManager;
public:
    explicit Script(lua_State* pState=NULL);
    virtual ~Script( void );

	// interface
	virtual void onInitialize(void);
	virtual void onHandleMessage(Packet* pPacket);
	virtual void onUpdate(void);
	virtual void onDestroy(void);

    inline void setInitString(const char* initFile){ m_initString = initFile; }
    inline const std::string& getInitString(void) const { return m_initString; }
	inline lua_State * getState( void ) { return m_pState; }
	inline int getStateID(void) const { return m_stateID; }
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
	inline void setStateID(int stateID){ m_stateID = stateID; }
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
    int m_stateID;
    std::string m_initString;
};//end class Script

NS_HIVENET_END

#endif
