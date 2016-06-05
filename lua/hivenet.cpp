/*
** Lua binding: hivenet
** Generated automatically by tolua++-1.0.92 on Sun Jun  5 12:37:27 2016.
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
 tolua_usertype(tolua_S,"Buffer");
 tolua_usertype(tolua_S,"HandlerQueue");
 tolua_usertype(tolua_S,"Packet");
 tolua_usertype(tolua_S,"RefObject");
 tolua_usertype(tolua_S,"ScriptManager");
 tolua_usertype(tolua_S,"Sync");
 tolua_usertype(tolua_S,"Script");
 tolua_usertype(tolua_S,"Thread");
 tolua_usertype(tolua_S,"UniqueHandle");
 tolua_usertype(tolua_S,"HandlerInterface");
 tolua_usertype(tolua_S,"LongUniqueHandle");
}

/* method: increase of class  UniqueHandle */
#ifndef TOLUA_DISABLE_tolua_hivenet_UniqueHandle_increase00
static int tolua_hivenet_UniqueHandle_increase00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UniqueHandle",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UniqueHandle* self = (UniqueHandle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'increase'", NULL);
#endif
  {
   self->increase();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'increase'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIndex of class  UniqueHandle */
#ifndef TOLUA_DISABLE_tolua_hivenet_UniqueHandle_setIndex00
static int tolua_hivenet_UniqueHandle_setIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UniqueHandle",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UniqueHandle* self = (UniqueHandle*)  tolua_tousertype(tolua_S,1,0);
  unsigned short index = ((unsigned short)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIndex'", NULL);
#endif
  {
   self->setIndex(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIndex of class  UniqueHandle */
#ifndef TOLUA_DISABLE_tolua_hivenet_UniqueHandle_getIndex00
static int tolua_hivenet_UniqueHandle_getIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UniqueHandle",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UniqueHandle* self = (const UniqueHandle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIndex'", NULL);
#endif
  {
   unsigned short tolua_ret = (unsigned short)  self->getIndex();
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

/* method: getVersion of class  UniqueHandle */
#ifndef TOLUA_DISABLE_tolua_hivenet_UniqueHandle_getVersion00
static int tolua_hivenet_UniqueHandle_getVersion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UniqueHandle",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UniqueHandle* self = (const UniqueHandle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVersion'", NULL);
#endif
  {
   unsigned short tolua_ret = (unsigned short)  self->getVersion();
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

/* method: getHandle of class  UniqueHandle */
#ifndef TOLUA_DISABLE_tolua_hivenet_UniqueHandle_getHandle00
static int tolua_hivenet_UniqueHandle_getHandle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UniqueHandle",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UniqueHandle* self = (const UniqueHandle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHandle'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->getHandle();
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

/* method: increase of class  LongUniqueHandle */
#ifndef TOLUA_DISABLE_tolua_hivenet_LongUniqueHandle_increase00
static int tolua_hivenet_LongUniqueHandle_increase00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LongUniqueHandle",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LongUniqueHandle* self = (LongUniqueHandle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'increase'", NULL);
#endif
  {
   self->increase();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'increase'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIndex of class  LongUniqueHandle */
#ifndef TOLUA_DISABLE_tolua_hivenet_LongUniqueHandle_setIndex00
static int tolua_hivenet_LongUniqueHandle_setIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LongUniqueHandle",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LongUniqueHandle* self = (LongUniqueHandle*)  tolua_tousertype(tolua_S,1,0);
  unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIndex'", NULL);
#endif
  {
   self->setIndex(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIndex of class  LongUniqueHandle */
#ifndef TOLUA_DISABLE_tolua_hivenet_LongUniqueHandle_getIndex00
static int tolua_hivenet_LongUniqueHandle_getIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LongUniqueHandle",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LongUniqueHandle* self = (const LongUniqueHandle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIndex'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->getIndex();
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

/* method: getVersion of class  LongUniqueHandle */
#ifndef TOLUA_DISABLE_tolua_hivenet_LongUniqueHandle_getVersion00
static int tolua_hivenet_LongUniqueHandle_getVersion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LongUniqueHandle",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LongUniqueHandle* self = (const LongUniqueHandle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVersion'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->getVersion();
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

/* method: getHandle of class  LongUniqueHandle */
#ifndef TOLUA_DISABLE_tolua_hivenet_LongUniqueHandle_getHandle00
static int tolua_hivenet_LongUniqueHandle_getHandle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LongUniqueHandle",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LongUniqueHandle* self = (const LongUniqueHandle*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHandle'", NULL);
#endif
  {
   unsigned long long tolua_ret = (unsigned long long)  self->getHandle();
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

/* method: getClassName of class  Packet */
#ifndef TOLUA_DISABLE_tolua_hivenet_Packet_getClassName00
static int tolua_hivenet_Packet_getClassName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Packet",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Packet* self = (const Packet*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: __Sync__ of class  HandlerInterface */
#ifndef TOLUA_DISABLE_tolua_get_HandlerInterface___Sync__
static int tolua_get_HandlerInterface___Sync__(lua_State* tolua_S)
{
  HandlerInterface* self = (HandlerInterface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__Sync__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<Sync*>(self), "Sync");
#else
   tolua_pushusertype(tolua_S,(void*)((Sync*)self), "Sync");
#endif
 return 1;
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

/* method: createInstance of class  HandlerQueue */
#ifndef TOLUA_DISABLE_tolua_hivenet_HandlerQueue_createInstance00
static int tolua_hivenet_HandlerQueue_createInstance00(lua_State* tolua_S)
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
   HandlerQueue* tolua_ret = (HandlerQueue*)  HandlerQueue::createInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"HandlerQueue");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: destroyInstance of class  HandlerQueue */
#ifndef TOLUA_DISABLE_tolua_hivenet_HandlerQueue_destroyInstance00
static int tolua_hivenet_HandlerQueue_destroyInstance00(lua_State* tolua_S)
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
   HandlerQueue::destroyInstance();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destroyInstance'.",&tolua_err);
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

/* get function: __Sync__ of class  HandlerQueue */
#ifndef TOLUA_DISABLE_tolua_get_HandlerQueue___Sync__
static int tolua_get_HandlerQueue___Sync__(lua_State* tolua_S)
{
  HandlerQueue* self = (HandlerQueue*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__Sync__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<Sync*>(self), "Sync");
#else
   tolua_pushusertype(tolua_S,(void*)((Sync*)self), "Sync");
#endif
 return 1;
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

/* method: createInstance of class  ScriptManager */
#ifndef TOLUA_DISABLE_tolua_hivenet_ScriptManager_createInstance00
static int tolua_hivenet_ScriptManager_createInstance00(lua_State* tolua_S)
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
   ScriptManager* tolua_ret = (ScriptManager*)  ScriptManager::createInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ScriptManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: destroyInstance of class  ScriptManager */
#ifndef TOLUA_DISABLE_tolua_hivenet_ScriptManager_destroyInstance00
static int tolua_hivenet_ScriptManager_destroyInstance00(lua_State* tolua_S)
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
   ScriptManager::destroyInstance();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destroyInstance'.",&tolua_err);
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
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScriptManager* self = (ScriptManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'create'", NULL);
#endif
  {
   Script* tolua_ret = (Script*)  self->create();
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
  int stateID = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'remove'", NULL);
#endif
  {
   self->remove(stateID);
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
  int stateID = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getScript'", NULL);
#endif
  {
   Script* tolua_ret = (Script*)  self->getScript(stateID);
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

/* get function: __Sync__ of class  ScriptManager */
#ifndef TOLUA_DISABLE_tolua_get_ScriptManager___Sync__
static int tolua_get_ScriptManager___Sync__(lua_State* tolua_S)
{
  ScriptManager* self = (ScriptManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__Sync__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<Sync*>(self), "Sync");
#else
   tolua_pushusertype(tolua_S,(void*)((Sync*)self), "Sync");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

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
  tolua_cclass(tolua_S,"UniqueHandle","UniqueHandle","",NULL);
  tolua_beginmodule(tolua_S,"UniqueHandle");
   tolua_function(tolua_S,"increase",tolua_hivenet_UniqueHandle_increase00);
   tolua_function(tolua_S,"setIndex",tolua_hivenet_UniqueHandle_setIndex00);
   tolua_function(tolua_S,"getIndex",tolua_hivenet_UniqueHandle_getIndex00);
   tolua_function(tolua_S,"getVersion",tolua_hivenet_UniqueHandle_getVersion00);
   tolua_function(tolua_S,"getHandle",tolua_hivenet_UniqueHandle_getHandle00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"LongUniqueHandle","LongUniqueHandle","",NULL);
  tolua_beginmodule(tolua_S,"LongUniqueHandle");
   tolua_function(tolua_S,"increase",tolua_hivenet_LongUniqueHandle_increase00);
   tolua_function(tolua_S,"setIndex",tolua_hivenet_LongUniqueHandle_setIndex00);
   tolua_function(tolua_S,"getIndex",tolua_hivenet_LongUniqueHandle_getIndex00);
   tolua_function(tolua_S,"getVersion",tolua_hivenet_LongUniqueHandle_getVersion00);
   tolua_function(tolua_S,"getHandle",tolua_hivenet_LongUniqueHandle_getHandle00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Buffer","Buffer","RefObject",NULL);
  tolua_beginmodule(tolua_S,"Buffer");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Packet","Packet","RefObject",NULL);
  tolua_beginmodule(tolua_S,"Packet");
   tolua_function(tolua_S,"getClassName",tolua_hivenet_Packet_getClassName00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"HandlerInterface","HandlerInterface","RefObject",NULL);
  tolua_beginmodule(tolua_S,"HandlerInterface");
   tolua_function(tolua_S,"getClassName",tolua_hivenet_HandlerInterface_getClassName00);
   tolua_variable(tolua_S,"__Sync__",tolua_get_HandlerInterface___Sync__,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"HandlerQueue","HandlerQueue","RefObject",NULL);
  tolua_beginmodule(tolua_S,"HandlerQueue");
   tolua_function(tolua_S,"getInstance",tolua_hivenet_HandlerQueue_getInstance00);
   tolua_function(tolua_S,"createInstance",tolua_hivenet_HandlerQueue_createInstance00);
   tolua_function(tolua_S,"destroyInstance",tolua_hivenet_HandlerQueue_destroyInstance00);
   tolua_function(tolua_S,"createWorker",tolua_hivenet_HandlerQueue_createWorker00);
   tolua_variable(tolua_S,"__Sync__",tolua_get_HandlerQueue___Sync__,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Script","Script","HandlerInterface",NULL);
  tolua_beginmodule(tolua_S,"Script");
   tolua_function(tolua_S,"getClassName",tolua_hivenet_Script_getClassName00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ScriptManager","ScriptManager","RefObject",NULL);
  tolua_beginmodule(tolua_S,"ScriptManager");
   tolua_function(tolua_S,"getInstance",tolua_hivenet_ScriptManager_getInstance00);
   tolua_function(tolua_S,"createInstance",tolua_hivenet_ScriptManager_createInstance00);
   tolua_function(tolua_S,"destroyInstance",tolua_hivenet_ScriptManager_destroyInstance00);
   tolua_function(tolua_S,"create",tolua_hivenet_ScriptManager_create00);
   tolua_function(tolua_S,"remove",tolua_hivenet_ScriptManager_remove00);
   tolua_function(tolua_S,"remove",tolua_hivenet_ScriptManager_remove01);
   tolua_function(tolua_S,"getScript",tolua_hivenet_ScriptManager_getScript00);
   tolua_function(tolua_S,"getMaster",tolua_hivenet_ScriptManager_getMaster00);
   tolua_function(tolua_S,"getClassName",tolua_hivenet_ScriptManager_getClassName00);
   tolua_variable(tolua_S,"__Sync__",tolua_get_ScriptManager___Sync__,NULL);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_hivenet (lua_State* tolua_S) {
 return tolua_hivenet_open(tolua_S);
};
#endif

