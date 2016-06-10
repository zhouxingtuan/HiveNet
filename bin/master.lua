--
-- Created by IntelliJ IDEA.
-- User: AppleTree
-- Date: 16/6/10
-- Time: 上午8:31
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

function onInitialize(pScript)
    print("onInitialize called cobj is", pScript:getClassName())
    require("test_luahiredis")
    require("test_luasql")
end

function onHandleMessage(handle, pPacket)
    print("onHandleMessage called handle", handle, "cobj is", pPacket:getClassName())
end

function onUpdate()

end

function onDestroy()
    print("onDestroy called")
end

function onAcceptIn(handle)
    print("onAcceptIn", handle)
end

function onAcceptOut(handle)
    print("onAcceptOut", handle)
end

function onClientIn(handle)
    print("onClientIn", handle)
end

function onClientOut(handle)
    print("onClientOut", handle)
end


