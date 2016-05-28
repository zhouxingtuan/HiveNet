/*
** Lua binding: hivenet
** Generated automatically by tolua++-1.0.92 on Sat May 28 14:20:28 2016.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_hivenet_open (lua_State* tolua_S);

#include "hivenet.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Thread");
 tolua_usertype(tolua_S,"Sync");
 tolua_usertype(tolua_S,"RefObject");
}

/* Open function */
TOLUA_API int tolua_hivenet_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"Sync","Sync","",NULL);
  tolua_beginmodule(tolua_S,"Sync");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"RefObject","RefObject","",NULL);
  tolua_beginmodule(tolua_S,"RefObject");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Thread","Thread","",NULL);
  tolua_beginmodule(tolua_S,"Thread");
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_hivenet (lua_State* tolua_S) {
 return tolua_hivenet_open(tolua_S);
};
#endif

