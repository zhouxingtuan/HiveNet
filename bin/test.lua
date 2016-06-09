--
-- Created by IntelliJ IDEA.
-- User: AppleTree
-- Date: 16/5/29
-- Time: 上午11:50
-- To change this template use File | Settings | File Templates.
--
print("-----------------")
local r, jit = pcall(require, 'jit')
if not r then
    print("jit close", jit)
else
    print("jit open", jit.version, jit.version_num, jit.os, jit.arch)
end
print("-----------------")
require("socket.init")
print("-----------------")
local luasql = require("luasql")
for k,v in pairs(luasql) do
    print(k, v)
end
print("-----------------")
local hiredis = require("hiredis")
for k,v in pairs(hiredis) do
    print(k,v)
end
print("-----------------")
--------------------------------------------------------------------------------
assert(type(hiredis.NIL == "table"))
assert(hiredis.NIL.name == "NIL")
assert(hiredis.NIL.type == hiredis.REPLY_NIL)
assert(tostring(hiredis.NIL) == "NIL")
assert(type(assert(getmetatable(hiredis.NIL))) == "string")
--------------------------------------------------------------------------------
local conn = assert(hiredis.connect("127.0.0.1", 6379))
assert(conn:command("PING") == hiredis.status.PONG)
conn:command("set", "hello", "Hello World!")
local hello = conn:command("get", "hello")
print("hello message from redis", hello)
--------------------------------------------------------------------------------
local env = luasql.mysql()
print("mysql env", env)
--local con = assert (env:connect("luasql-test"))
--print("mysql con", con)

env:close()

function onInitialize(pScript)
    print("onInitialize called cobj is", pScript:getClassName())
end

function onHandleMessage(pPacket)
    print("onHandleMessage called cobj is", pPacket:getClassName())
end

function onUpdate()
    print("onUpdate called")
end

function onDestroy()
    print("onDestroy called")
end
