--
-- Created by IntelliJ IDEA.
-- User: AppleTree
-- Date: 16/6/10
-- Time: 上午8:29
-- To change this template use File | Settings | File Templates.
--

-- 创建工作线程的数量，最好是CPU核数量的2倍
HandlerQueue:getInstance():createWorker(4)

-- 设置master的加载脚本
local master = ScriptManager:getInstance():getMaster()
master:setInitString("require('master')")

-- 设置epoll的ip和端口
Epoll:getInstance():setListenSocket("127.0.0.1", 8888)
