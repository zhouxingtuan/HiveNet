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
	ScriptManager::createInstance();

	int value = 1000;
	Packet* p = new Packet(120);
	p->retain();
	p->write(&value, sizeof(value));
	p->resetCursor();
	int value2 = 0;
	p->read(&value2, sizeof(value2));
	fprintf(stderr, "value is %d and after write read value2 is %d \n", value, value2);
	fprintf(stderr, "p getRefCount %d\n", p->getRefCount());

	Script* pScript = ScriptManager::getInstance()->create();
	pScript->setInitString("print('Hello World From Lua') require('test')");
	pScript->onInitialize();
	pScript->onHandleMessage(p);
	pScript->onUpdate();
	pScript->onDestroy();
	ScriptManager::destroyInstance();

	p->release();

	return 0;
}
