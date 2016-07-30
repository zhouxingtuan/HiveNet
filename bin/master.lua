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
local loop = 50000
local write_num = 200
local string = string
local char = string.char
local byte = string.byte
local test_write_read = function()
    local pcks = {}
    for k=1,loop do
        local p = Packet:createPacket(write_num+4)
        p:retain()
        pcks[k] = p
        p:setCursor(4)
    end
    local t1 = os.clock()
    for l=1,loop do
        local p = pcks[l]
        for k=1,write_num do
            p:writeByte(k)
        end
    end
    local t2 = os.clock()
    print("writeByte num", write_num, "loop", loop, "cost", t2-t1)
    for l=1,loop do
        local p = pcks[l]
        p:setCursor(4)
    end
    local t1 = os.clock()
    local arr = {}
    for l=1,loop do
        arr = {}
        local p = pcks[l]
        for k=1,write_num do
            local b = p:readByte()
            table.insert(arr, b)
        end
    end
    local t2 = os.clock()
--    print("read value", table.concat(arr, ","))
    print("readByte num", write_num, "loop", loop, "cost", t2-t1)
    for k,p in pairs(pcks) do
        p:release()
    end
end

local test_write_read_once = function()
    local pcks = {}
    for k=1,loop do
        local p = Packet:createPacket(write_num+4)
        p:retain()
        pcks[k] = p
        p:setCursor(4)
    end
    local t1 = os.clock()
    for l=1,loop do
        local p = pcks[l]
        local buf = {}
        for k=1,write_num do
            table.insert(buf, char(k))
        end
        local str = table.concat(buf)
        p:write(str, string.len(str))
    end
    local t2 = os.clock()
    print("write once num", write_num, "loop", loop, "cost", t2-t1)
    for l=1,loop do
        local p = pcks[l]
        p:setCursor(4)
    end
    local arr = {}
    local t1 = os.clock()
    for l=1,loop do
        arr = {}
        local p = pcks[l]
        local str = p:read()
        local len = string.len(str)
        for k=1,len do
            local b = byte(str:sub(k, k))
            table.insert(arr, b)
        end
    end
    local t2 = os.clock()
--    print("read value", table.concat(arr, ","))
    print("read once num", write_num, "loop", loop, "cost", t2-t1)
    for k,p in pairs(pcks) do
        p:release()
    end
end

function onTestMessage(packet)
    print("onTestMessage called")
    test_write_read()
    test_write_read_once()
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


