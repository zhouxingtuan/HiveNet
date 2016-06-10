//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/6/9
// Time: 下午10:29
// To change this template use File | Settings | File Templates.
//

#include "uniquemanager.h"

NS_HIVENET_BEGIN

static UniqueManager* g_pUniqueManager = NULL;
UniqueManager::UniqueManager() : RefObject(), Sync() {

}
UniqueManager::~UniqueManager(){
	releaseObjects();
}
UniqueManager* UniqueManager::getInstance(void){
	return g_pUniqueManager;
}
UniqueManager* UniqueManager::createInstance(void){
	if(g_pUniqueManager == NULL){
		g_pUniqueManager = new UniqueManager();
		SAFE_RETAIN(g_pUniqueManager)
	}
	return g_pUniqueManager;
}
void UniqueManager::destroyInstance(void){
    SAFE_RELEASE(g_pUniqueManager)
}
void UniqueManager::releaseObjects(void){
	lock();
	for( auto pUnique : m_uniqueObjects ){
		if( NULL != pUnique ){
			pUnique->release();
		}
	}
	m_uniqueObjects.clear();
	unlock();
}
void UniqueManager::registerCreateFunction(unique_char uniqueType, CreateFunction func){
	lock();
	if(uniqueType >= m_createFunctions.size()){
		m_createFunctions.resize(uniqueType+1);
		m_idleIndex.resize(uniqueType+1);
	}
	m_createFunctions[uniqueType] = func;
	unlock();
}
Unique* UniqueManager::create(unique_char uniqueType){
	unique_int index;
    Unique* pUnique;
    lock();
    IntVector& idles = m_idleIndex[uniqueType];
    if( !idles.empty() ){
    	index = idles.back();
    	idles.pop_back();
		pUnique = m_uniqueObjects[index];
		if( NULL == pUnique ){
			pUnique = m_createFunctions[uniqueType](uniqueType);
			pUnique->retain();
			pUnique->setIndex(index);
			m_uniqueObjects[index] = pUnique;
		}
    }else{
    	index = (unique_int)m_uniqueObjects.size();
    	pUnique = m_createFunctions[uniqueType](uniqueType);
		pUnique->retain();
		pUnique->setIndex(index);
		m_uniqueObjects.push_back(pUnique);
    }
    unlock();
	return pUnique;
}
Unique* UniqueManager::getByHandle(unique_long handle){
	Unique* pUnique = NULL;
	UniqueHandle h = handle;
	unique_int index = h.getIndex();
	lock();
	if( index < (unique_int)m_uniqueObjects.size() ){
		pUnique = m_uniqueObjects[index];
	}
	unlock();
	if( NULL != pUnique && pUnique->getHandle() != handle ){
		return NULL;
	}
	return pUnique;
}
void UniqueManager::idle(Unique* pUnique){
	idle(pUnique->getHandle());
}
void UniqueManager::idle(unique_long handle){
	Unique* pUnique = NULL;
	UniqueHandle h = handle;
	unique_int index = h.getIndex();
	lock();
	if( index < (unique_int)m_uniqueObjects.size() ){
		pUnique = m_uniqueObjects[index];
		if( NULL != pUnique ){
			if( pUnique->getHandle() == handle ){
				pUnique->increaseVersion();	// 这里对这个对象进行了重复使用
				IntVector& idles = m_idleIndex[pUnique->getType()];
				idles.push_back(index);
			}else{
				pUnique = NULL;
			}
		}
    }
	unlock();
}
void UniqueManager::remove(Unique* pUnique){
	remove(pUnique->getHandle());
}
void UniqueManager::remove(unique_long handle){
	Unique* pUnique = NULL;
	UniqueHandle h = handle;
	unique_int index = h.getIndex();
    lock();
    if( index < (unique_int)m_uniqueObjects.size() ){
		pUnique = m_uniqueObjects[index];
		m_uniqueObjects[index] = NULL;
		if( NULL != pUnique ){
			if(handle == pUnique->getHandle()){
				IntVector& idles = m_idleIndex[pUnique->getType()];
				idles.push_back(index);
			}else{
				pUnique = NULL;
			}
		}
    }
	unlock();
	if( NULL != pUnique ){
		pUnique->release();
	}
}
void UniqueManager::removeByType(unique_char uniqueType){
	UniqueVector vecRemove;
	lock();
	IntVector& idles = m_idleIndex[uniqueType];
	for( auto pUnique : m_uniqueObjects ){
		if( NULL != pUnique && pUnique->getType() == uniqueType ){
			idles.push_back(pUnique->getIndex());
			m_uniqueObjects[pUnique->getIndex()] = NULL;
			vecRemove.push_back(pUnique);
		}
	}
	unlock();
	for( auto pUnique : vecRemove ){
		pUnique->release();
	}
}
void UniqueManager::loop(unique_char uniqueType, LoopFunction loopFunc){
	UniqueVector vecObj;
	lock();
	for( auto pUnique : m_uniqueObjects ){
		if( NULL != pUnique && pUnique->getType() == uniqueType ){
			pUnique->retain();
			vecObj.push_back(pUnique);
		}
	}
	unlock();
	for( auto pUnique : vecObj ){
		loopFunc(pUnique);
		pUnique->release();
	}
}

NS_HIVENET_END
