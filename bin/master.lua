--
-- Created by IntelliJ IDEA.
-- User: AppleTree
-- Date: 16/6/10
-- Time: 上午8:31
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

local m_pScript
function onInitialize(pScript)
    m_pScript = pScript
    print("onInitialize called cobj is", pScript:getClassName())
--    require("test_luahiredis")
--    require("test_luasql")
end

function onHandleMessage(handle, msg)
    print("onHandleMessage called handle", handle, "msg is", msg)
end

local count = 0
local isCreated = false
function onUpdate()
    if not isCreated then
        count = count + 1
        if count > 30 then
            isCreated = true
            local ip = "127.0.0.1"
            local port = 8888
            local handle = Epoll:getInstance():createClient(ip, port)
            print("createClient to", ip, port, "handle", handle)
        end
    end
end

function onDestroy()
    print("onDestroy called")
end

function onAcceptIn(handle)
    print("onAcceptIn", tostring(handle))
    local ret = m_pScript:sendMessage(handle, "Hello From Server!")
    print("onAcceptIn sendMessage", ret)
    local scriptObj = ScriptManager:getInstance():create("require('branch')")
    print("scriptObj handle", scriptObj:getHandle(), scriptObj:getType(), scriptObj:getIndex(), scriptObj:getVersion())
    -- 连接需要设置为已验证，才能够打开底层接收大量数据的开关，未验证只能接收64字节，已验证可以接收最大64M可以自己去更改并编译
    Epoll:getInstance():setIdentify(handle, true)
end

function onAcceptOut(handle)
    print("onAcceptOut", tostring(handle))
end

function onClientIn(handle)
    print("onClientIn", tostring(handle))
    local ret = m_pScript:sendMessage(handle, "Hello From Client!")
    print("onClientIn sendMessage", ret)
end

function onClientOut(handle)
    print("onClientOut", tostring(handle))
end


