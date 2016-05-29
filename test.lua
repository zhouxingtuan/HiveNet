--
-- Created by IntelliJ IDEA.
-- User: AppleTree
-- Date: 16/5/29
-- Time: 上午11:50
-- To change this template use File | Settings | File Templates.
--

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
