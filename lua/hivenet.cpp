/*
** Lua binding: hivenet
** Generated automatically by tolua++-1.0.92 on Wed Jun 15 22:54:14 2016.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_hivenet_open (lua_State* tolua_S);

#include "hivenet.h"
#include "script.h"
#include "scriptmanager.h"
#include "manual.hpp"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Epoll");
 tolua_usertype(tolua_S,"Unique");
 tolua_usertype(tolua_S,"HandlerQueue");
 tolua_usertype(tolua_S,"ScriptManager");
 tolua_usertype(tolua_S,"HandlerInterface");
 tolua_usertype(tolua_S,"Script");
}

/* method: getIndex of class  Unique */
#ifndef TOLUA_DISABLE_tolua_hivenet_Unique_getIndex00
static int tolua_hivenet_Unique_getIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Unique",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Unique* self = (const Unique*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIndex'", NULL);
#endif
  {
   unsigned int tolua_ret = ( unsigned int)  self->getIndex();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVersion of class  Unique */
#ifndef TOLUA_DISABLE_tolua_hivenet_Unique_getVersion00
static int tolua_hivenet_Unique_getVersion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Unique",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Unique* self = (const Unique*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVersion'", NULL);
#endif
  {
   unsigned short tolua_ret = ( unsigned short)  self->getVersion();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVersion'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getHandle of class  Unique */
#ifndef TOLUA_DISABLE_tolua_hivenet_Unique_getHandle00
static int tolua_hivenet_Unique_getHandle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Unique",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Unique* self = (const Unique*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHandle'", NULL);
#endif
  {
   long long tolua_ret = ( long long)  self->getHandle();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getType of class  Unique */
#ifndef TOLUA_DISABLE_tolua_hivenet_Unique_getType00
static int tolua_hivenet_Unique_getType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Unique",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Unique* self = (const Unique*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getType'", NULL);
#endif
  {
   unsigned char tolua_ret = ( unsigned char)  self->getType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getClassName of class  Unique */
#ifndef TOLUA_DISABLE_tolua_hivenet_Unique_getClassName00
static int tolua_hivenet_Unique_getClassName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Unique",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Unique* self = (const Unique*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getClassName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getClassName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getClassName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: releaseTask of class  HandlerInterface */
#ifndef TOLUA_DISABLE_tolua_hivenet_HandlerInterface_releaseTask00
static int tolua_hivenet_HandlerInterface_releaseTask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HandlerInterface",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HandlerInterface* self = (HandlerInterface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'releaseTask'", NULL);
#endif
  {
   self->releaseTask();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'releaseTask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getClassName of class  HandlerInterface */
#ifndef TOLUA_DISABLE_tolua_hivenet_HandlerInterface_getClassName00
static int tolua_hivenet_HandlerInterface_getClassName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const HandlerInterface",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const HandlerInterface* self = (const HandlerInterface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getClassName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getClassName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getClassName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInstance of class  HandlerQueue */
#ifndef TOLUA_DISABLE_tolua_hivenet_HandlerQueue_getInstance00
static int tolua_hivenet_HandlerQueue_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"HandlerQueue",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   HandlerQueue* tolua_ret = (HandlerQueue*)  HandlerQueue::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"HandlerQueue");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWorker of class  HandlerQueue */
#ifndef TOLUA_DISABLE_tolua_hivenet_HandlerQueue_createWorker00
static int tolua_hivenet_HandlerQueue_createWorker00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HandlerQueue",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HandlerQueue* self = (HandlerQueue*)  tolua_tousertype(tolua_S,1,0);
  int workerNumber = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createWorker'", NULL);
#endif
  {
   self->createWorker(workerNumber);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWorker'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getClassName of class  HandlerQueue */
#ifndef TOLUA_DISABLE_tolua_hivenet_HandlerQueue_getClassName00
static int tolua_hivenet_HandlerQueue_getClassName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const HandlerQueue",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const HandlerQueue* self = (const HandlerQueue*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getClassName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getClassName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getClassName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInstance of class  Epoll */
#ifndef TOLUA_DISABLE_tolua_hivenet_Epoll_getInstance00
static int tolua_hivenet_Epoll_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Epoll",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Epoll* tolua_ret = (Epoll*)  Epoll::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Epoll");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIdentify of class  Epoll */
#ifndef TOLUA_DISABLE_tolua_hivenet_Epoll_setIdentify00
static int tolua_hivenet_Epoll_setIdentify00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Epoll",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Epoll* self = (Epoll*)  tolua_tousertype(tolua_S,1,0);
  long long handle = (( long long)  tolua_tonumber(tolua_S,2,0));
  bool identify = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIdentify'", NULL);
#endif
  {
   self->setIdentify(handle,identify);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIdentify'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createClient of class  Epoll */
#ifndef TOLUA_DISABLE_tolua_hivenet_Epoll_createClient00
static int tolua_hivenet_Epoll_createClient00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Epoll",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Epoll* self = (Epoll*)  tolua_tousertype(tolua_S,1,0);
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned short port = ((unsigned short)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createClient'", NULL);
#endif
  {
   long long tolua_ret = ( long long)  self->createClient(ip,port);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createClient'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: closeClient of class  Epoll */
#ifndef TOLUA_DISABLE_tolua_hivenet_Epoll_closeClient00
static int tolua_hivenet_Epoll_closeClient00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Epoll",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Epoll* self = (Epoll*)  tolua_tousertype(tolua_S,1,0);
  long long handle = (( long long)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'closeClient'", NULL);
#endif
  {
   self->closeClient(handle);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'closeClient'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: closeAccept of class  Epoll */
#ifndef TOLUA_DISABLE_tolua_hivenet_Epoll_closeAccept00
static int tolua_hivenet_Epoll_closeAccept00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Epoll",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Epoll* self = (Epoll*)  tolua_tousertype(tolua_S,1,0);
  long long handle = (( long long)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'closeAccept'", NULL);
#endif
  {
   self->closeAccept(handle);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'closeAccept'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setListenSocket of class  Epoll */
#ifndef TOLUA_DISABLE_tolua_hivenet_Epoll_setListenSocket00
static int tolua_hivenet_Epoll_setListenSocket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Epoll",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Epoll* self = (Epoll*)  tolua_tousertype(tolua_S,1,0);
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned short port = ((unsigned short)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setListenSocket'", NULL);
#endif
  {
   self->setListenSocket(ip,port);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setListenSocket'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: closeEpoll of class  Epoll */
#ifndef TOLUA_DISABLE_tolua_hivenet_Epoll_closeEpoll00
static int tolua_hivenet_Epoll_closeEpoll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Epoll",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Epoll* self = (Epoll*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'closeEpoll'", NULL);
#endif
  {
   self->closeEpoll();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'closeEpoll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getClassName of class  Epoll */
#ifndef TOLUA_DISABLE_tolua_hivenet_Epoll_getClassName00
static int tolua_hivenet_Epoll_getClassName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Epoll",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Epoll* self = (const Epoll*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getClassName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getClassName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getClassName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sendMessage of class  Script */
#ifndef TOLUA_DISABLE_tolua_hivenet_Script_sendMessage00
static int tolua_hivenet_Script_sendMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Script",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Script* self = (Script*)  tolua_tousertype(tolua_S,1,0);
  long long handle = (( long long)  tolua_tonumber(tolua_S,2,0));
  const char* pData = ((const char*)  tolua_tostring(tolua_S,3,0));
  unsigned int length = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendMessage'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->sendMessage(handle,pData,length);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInitString of class  Script */
#ifndef TOLUA_DISABLE_tolua_hivenet_Script_setInitString00
static int tolua_hivenet_Script_setInitString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Script",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Script* self = (Script*)  tolua_tousertype(tolua_S,1,0);
  const char* initFile = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInitString'", NULL);
#endif
  {
   self->setInitString(initFile);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInitString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInitString of class  Script */
#ifndef TOLUA_DISABLE_tolua_hivenet_Script_getInitString00
static int tolua_hivenet_Script_getInitString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Script",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Script* self = (const Script*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getInitString'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->getInitString();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInitString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getClassName of class  Script */
#ifndef TOLUA_DISABLE_tolua_hivenet_Script_getClassName00
static int tolua_hivenet_Script_getClassName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Script",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Script* self = (const Script*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getClassName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getClassName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getClassName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInstance of class  ScriptManager */
#ifndef TOLUA_DISABLE_tolua_hivenet_ScriptManager_getInstance00
static int tolua_hivenet_ScriptManager_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ScriptManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ScriptManager* tolua_ret = (ScriptManager*)  ScriptManager::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ScriptManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  ScriptManager */
#ifndef TOLUA_DISABLE_tolua_hivenet_ScriptManager_create00
static int tolua_hivenet_ScriptManager_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScriptManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScriptManager* self = (ScriptManager*)  tolua_tousertype(tolua_S,1,0);
  const char* initString = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'create'", NULL);
#endif
  {
   Script* tolua_ret = (Script*)  self->create(initString);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Script");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: idle of class  ScriptManager */
#ifndef TOLUA_DISABLE_tolua_hivenet_ScriptManager_idle00
static int tolua_hivenet_ScriptManager_idle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScriptManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScriptManager* self = (ScriptManager*)  tolua_tousertype(tolua_S,1,0);
  long long handle = (( long long)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'idle'", NULL);
#endif
  {
   self->idle(handle);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'idle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: idle of class  ScriptManager */
#ifndef TOLUA_DISABLE_tolua_hivenet_ScriptManager_idle01
static int tolua_hivenet_ScriptManager_idle01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScriptManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Script",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ScriptManager* self = (ScriptManager*)  tolua_tousertype(tolua_S,1,0);
  Script* pScript = ((Script*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'idle'", NULL);
#endif
  {
   self->idle(pScript);
  }
 }
 return 0;
tolua_lerror:
 return tolua_hivenet_ScriptManager_idle00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: remove of class  ScriptManager */
#ifndef TOLUA_DISABLE_tolua_hivenet_ScriptManager_remove00
static int tolua_hivenet_ScriptManager_remove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScriptManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScriptManager* self = (ScriptManager*)  tolua_tousertype(tolua_S,1,0);
  long long handle = (( long long)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'remove'", NULL);
#endif
  {
   self->remove(handle);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'remove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: remove of class  ScriptManager */
#ifndef TOLUA_DISABLE_tolua_hivenet_ScriptManager_remove01
static int tolua_hivenet_ScriptManager_remove01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScriptManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Script",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ScriptManager* self = (ScriptManager*)  tolua_tousertype(tolua_S,1,0);
  Script* pScript = ((Script*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'remove'", NULL);
#endif
  {
   self->remove(pScript);
  }
 }
 return 0;
tolua_lerror:
 return tolua_hivenet_ScriptManager_remove00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getScript of class  ScriptManager */
#ifndef TOLUA_DISABLE_tolua_hivenet_ScriptManager_getScript00
static int tolua_hivenet_ScriptManager_getScript00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScriptManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScriptManager* self = (ScriptManager*)  tolua_tousertype(tolua_S,1,0);
  long long handle = (( long long)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getScript'", NULL);
#endif
  {
   Script* tolua_ret = (Script*)  self->getScript(handle);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Script");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getScript'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMaster of class  ScriptManager */
#ifndef TOLUA_DISABLE_tolua_hivenet_ScriptManager_getMaster00
static int tolua_hivenet_ScriptManager_getMaster00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScriptManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScriptManager* self = (ScriptManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaster'", NULL);
#endif
  {
   Script* tolua_ret = (Script*)  self->getMaster();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Script");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMaster'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getClassName of class  ScriptManager */
#ifndef TOLUA_DISABLE_tolua_hivenet_ScriptManager_getClassName00
static int tolua_hivenet_ScriptManager_getClassName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ScriptManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ScriptManager* self = (const ScriptManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getClassName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getClassName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getClassName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_hivenet_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"Unique","Unique","",NULL);
  tolua_beginmodule(tolua_S,"Unique");
   tolua_function(tolua_S,"getIndex",tolua_hivenet_Unique_getIndex00);
   tolua_function(tolua_S,"getVersion",tolua_hivenet_Unique_getVersion00);
   tolua_function(tolua_S,"getHandle",tolua_hivenet_Unique_getHandle00);
   tolua_function(tolua_S,"getType",tolua_hivenet_Unique_getType00);
   tolua_function(tolua_S,"getClassName",tolua_hivenet_Unique_getClassName00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"HandlerInterface","HandlerInterface","Unique",NULL);
  tolua_beginmodule(tolua_S,"HandlerInterface");
   tolua_function(tolua_S,"releaseTask",tolua_hivenet_HandlerInterface_releaseTask00);
   tolua_function(tolua_S,"getClassName",tolua_hivenet_HandlerInterface_getClassName00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"HandlerQueue","HandlerQueue","",NULL);
  tolua_beginmodule(tolua_S,"HandlerQueue");
   tolua_function(tolua_S,"getInstance",tolua_hivenet_HandlerQueue_getInstance00);
   tolua_function(tolua_S,"createWorker",tolua_hivenet_HandlerQueue_createWorker00);
   tolua_function(tolua_S,"getClassName",tolua_hivenet_HandlerQueue_getClassName00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Epoll","Epoll","",NULL);
  tolua_beginmodule(tolua_S,"Epoll");
   tolua_function(tolua_S,"getInstance",tolua_hivenet_Epoll_getInstance00);
   tolua_function(tolua_S,"setIdentify",tolua_hivenet_Epoll_setIdentify00);
   tolua_function(tolua_S,"createClient",tolua_hivenet_Epoll_createClient00);
   tolua_function(tolua_S,"closeClient",tolua_hivenet_Epoll_closeClient00);
   tolua_function(tolua_S,"closeAccept",tolua_hivenet_Epoll_closeAccept00);
   tolua_function(tolua_S,"setListenSocket",tolua_hivenet_Epoll_setListenSocket00);
   tolua_function(tolua_S,"closeEpoll",tolua_hivenet_Epoll_closeEpoll00);
   tolua_function(tolua_S,"getClassName",tolua_hivenet_Epoll_getClassName00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Script","Script","HandlerInterface",NULL);
  tolua_beginmodule(tolua_S,"Script");
   tolua_function(tolua_S,"sendMessage",tolua_hivenet_Script_sendMessage00);
   tolua_function(tolua_S,"setInitString",tolua_hivenet_Script_setInitString00);
   tolua_function(tolua_S,"getInitString",tolua_hivenet_Script_getInitString00);
   tolua_function(tolua_S,"getClassName",tolua_hivenet_Script_getClassName00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ScriptManager","ScriptManager","",NULL);
  tolua_beginmodule(tolua_S,"ScriptManager");
   tolua_function(tolua_S,"getInstance",tolua_hivenet_ScriptManager_getInstance00);
   tolua_function(tolua_S,"create",tolua_hivenet_ScriptManager_create00);
   tolua_function(tolua_S,"idle",tolua_hivenet_ScriptManager_idle00);
   tolua_function(tolua_S,"idle",tolua_hivenet_ScriptManager_idle01);
   tolua_function(tolua_S,"remove",tolua_hivenet_ScriptManager_remove00);
   tolua_function(tolua_S,"remove",tolua_hivenet_ScriptManager_remove01);
   tolua_function(tolua_S,"getScript",tolua_hivenet_ScriptManager_getScript00);
   tolua_function(tolua_S,"getMaster",tolua_hivenet_ScriptManager_getMaster00);
   tolua_function(tolua_S,"getClassName",tolua_hivenet_ScriptManager_getClassName00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_hivenet (lua_State* tolua_S) {
 return tolua_hivenet_open(tolua_S);
};
#endif

