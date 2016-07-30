--
-- Created by IntelliJ IDEA.
-- User: AppleTree
-- Date: 16/5/29
-- Time: 上午11:50
-- To change this template use File | Settings | File Templates.
--

local r, jit = pcall(require, 'jit')
require("socket.init")
local luasql = require("luasql")
local hiredis = require("hiredis")

--print("-----------------")
--if not r then
--    print("jit close", jit)
--else
--    print("jit open", jit.version, jit.version_num, jit.os, jit.arch)
--end
--print("-----------------")
--print("-----------------")
--for k,v in pairs(luasql) do
--    print(k, v)
--end
--print("-----------------")
--for k,v in pairs(hiredis) do
--    print(k,v)
--end
--print("-----------------")

function onInitialize(pScript)
    print("onInitialize called cobj is", pScript:getClassName())
--    require("test_luahiredis")
--    require("test_luasql")
end

function onHandleMessage(handle, msg)
    print("onHandleMessage called handle", handle, "msg is", msg)
end

function onTestMessage(packet)

end

function onUpdate()

end

function onDestroy()
    print("onDestroy called")
end
