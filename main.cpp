//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/28
// Time: 下午12:48
// To change this template use File | Settings | File Templates.
//

#include "hivenet.h"
#include "scriptmanager.h"

// 重新定义C++的内存分配函数，由jemalloc来进行内存分配
void* operator new(size_t size){
	return je_malloc(size);
}
void* operator new(size_t size, const std::nothrow_t& nothrow_value){
	return je_malloc(size);
}
void operator delete(void* p){
	je_free(p);
}
void* operator new[](size_t size){
	return je_malloc(size);
}
void* operator new[](size_t size, const std::nothrow_t& nothrow_value){
	return je_malloc(size);
}
void operator delete[](void* p){
	je_free(p);
}

USING_NS_HIVENET;

int main(int argc, char *argv[])
{
	fprintf(stderr, "hello world!\n");
	// 单例创建
	UniqueManager::createInstance();
	UniqueManager::getInstance()->registerCreateFunction(UNIQUE_HANDLER_ACCEPT, Accept::CreateFunction);
	UniqueManager::getInstance()->registerCreateFunction(UNIQUE_HANDLER_CLIENT, Client::CreateFunction);
	UniqueManager::getInstance()->registerCreateFunction(UNIQUE_HANDLER_SCRIPT, Script::CreateFunction);
	HandlerQueue::createInstance();
	ScriptManager::createInstance();
	Epoll::createInstance();

	// 使用master脚本加载init.lua文件
	Script* pMaster = ScriptManager::getInstance()->getMaster();
	Epoll::getInstance()->setFactory(pMaster);	// 将master脚本设置成为
	std::string init = "require('init')";
	if( !pMaster->executeText(init.c_str(), init.length()) ){
		fprintf(stderr, "init.lua file for initialize can not be found\n");
		goto MAIN_EXIT;
	}
	if( !Epoll::getInstance()->initialize() ){
		fprintf(stderr, "epoll initialize failed main exit\n");
		goto MAIN_EXIT;
	}
	// 初始化master脚本，调用该脚本的初始化函数
	pMaster->onInitialize();
	// 开始定时器// 纳秒级别，每秒更新10次就是100毫秒
	if( !ScriptManager::getInstance()->startTimer(0, 100000000) ){
		fprintf(stderr, "ScriptManager startTimer failed main exit\n");
		goto MAIN_EXIT;
	}
	while(true){
		if( !Epoll::getInstance()->update() ){
			fprintf(stderr, "epoll update return false main exit\n");
			break;
		}
	};
	pMaster->onDestroy();

MAIN_EXIT:
	sleep(3);
	Epoll::destroyInstance();
	ScriptManager::destroyInstance();
	HandlerQueue::destroyInstance();
	UniqueManager::destroyInstance();

	return 0;
}
