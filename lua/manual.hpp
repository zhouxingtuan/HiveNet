//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/29
// Time: 上午10:03
// To change this template use File | Settings | File Templates.
//

#include "lua.hpp"
#include "tolua++.h"

#include "scriptmanager.h"

USING_NS_HIVENET

/* Exported function */
TOLUA_API int  tolua_hivenet_open (lua_State* tolua_S);

#define TOLUA_DISABLE_tolua_hivenet_Script_sendMessage00
static int tolua_hivenet_Script_sendMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Script",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int length;
  Script* self = (Script*)  tolua_tousertype(tolua_S,1,0);
  long long handle = (( long long)  tolua_tonumber(tolua_S,2,0));
//  fprintf(stderr, "get handle %lld\n", handle);
  const char* pData = ((const char*)  lua_tolstring(tolua_S,3,&length));
//  fprintf(stderr, "get msg %s\n", pData);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendMessage'", NULL);
#endif
  {
   unsigned int totalLength = length + PACKET_HEAD_LENGTH;
   Packet* pPacket = new Packet(totalLength);
   pPacket->retain();
   pPacket->write(&totalLength, PACKET_HEAD_LENGTH);	// 写入头部数据
   pPacket->write(pData, length);						// 写入数据
   bool tolua_ret = (bool)  self->sendMessage(handle,pPacket);
//   fprintf(stderr, "after sendMessage\n");
   pPacket->release();
//   fprintf(stderr, "after pPacket->release\n");
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


/* method: read of class  Packet */
#define TOLUA_DISABLE_tolua_hivenet_Packet_read00
static int tolua_hivenet_Packet_read00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Packet",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Packet* self = (Packet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'read'", NULL);
#endif
  {
   lua_pushlstring(tolua_S,self->getCursorPtr(),self->getLength()-self->getCursor());
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'read'.",&tolua_err);
 return 0;
#endif
}
