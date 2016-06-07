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
require("luasql")
for k,v in pairs(luasql) do
    print(k, v)
end
print("-----------------")
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
