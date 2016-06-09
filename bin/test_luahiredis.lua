--
-- Created by IntelliJ IDEA.
-- User: AppleTree
-- Date: 16/6/9
-- Time: 下午5:55
-- To change this template use File | Settings | File Templates.
--

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
