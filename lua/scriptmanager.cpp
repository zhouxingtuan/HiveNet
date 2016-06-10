//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/5/29
// Time: 上午9:12
// To change this template use File | Settings | File Templates.
//

#include "scriptmanager.h"

NS_HIVENET_BEGIN

static ScriptManager* g_pScriptManager = NULL;
ScriptManager::ScriptManager() : RefObject(), m_pMaster(NULL) {
	openMaster();
}
ScriptManager::~ScriptManager(){
	closeMaster();
}
ScriptManager* ScriptManager::getInstance(void){
	return g_pScriptManager;
}
ScriptManager* ScriptManager::createInstance(void){
	if(g_pScriptManager == NULL){
		g_pScriptManager = new ScriptManager();
		SAFE_RETAIN(g_pScriptManager)
	}
	return g_pScriptManager;
}
void ScriptManager::destroyInstance(void){
    SAFE_RELEASE(g_pScriptManager)
}
bool ScriptManager::sendPacket(unique_long handle, Packet* pPacket){
	Script* pScript = this->getScript(handle);
	if( NULL != pScript ){
		TaskHandleMessage* pTask = new TaskHandleMessage(pScript, handle, pPacket);
		pTask->commitTask();
		return true;
	}
	return false;
}
//创建一个Script
Script* ScriptManager::create(const char* initString){
	Script* pScript = (Script*)UniqueManager::getInstance()->create(UNIQUE_HANDLER_SCRIPT);
	if( NULL == pScript->getState() ){
		pScript->setMaster(m_pMaster);
		pScript->setState(NULL);
		pScript->setInitString(initString);
	}
	TaskInitialize* pTask = new TaskInitialize(pScript);
	pTask->commitTask();
	return pScript;
}
void ScriptManager::idle(unique_long handle){
	Script* pScript = getScript(handle);
	if( NULL != pScript ){
		TaskDestroy* pTask = new TaskDestroy(pScript);
		pTask->commitTask();
//		UniqueManager::getInstance()->idle(this);	// 这里比较特别，不马上标记为不可用，因为还有后续TaskDestroy要执行
	}
}
void ScriptManager::idle(Script* pScript){
	idle( pScript->getHandle() );
}
void ScriptManager::remove(unique_long handle){
	Script* pScript = getScript(handle);
	if( NULL != pScript ){
		TaskDestroy* pTask = new TaskDestroy(pScript);
		pTask->commitTask();
		UniqueManager::getInstance()->remove(handle);
	}
}
void ScriptManager::remove(Script* script){
    remove( script->getHandle() );
}
Script* ScriptManager::getScript(unique_long handle){
	UniqueHandle h = handle;
	unique_char handlerType = h.getType();
	if( handlerType != UNIQUE_HANDLER_SCRIPT ){
		return NULL;
	}
	Unique* pUnique = UniqueManager::getInstance()->getByHandle(handle);
	if( NULL == pUnique ){
		return NULL;
	}
	return (Script*)pUnique;
}
//打开当前的Lua状态机
void ScriptManager::openMaster(void){
	if( m_pMaster == NULL ){
		lua_State* state = lua_open();
		if( state ){
			m_pMaster = (Script*)UniqueManager::getInstance()->create(UNIQUE_HANDLER_SCRIPT);
			m_pMaster->setState(state);
			m_pMaster->retain();
		}
	}
}
//关闭当前的Lua状态机
void ScriptManager::closeMaster(void){
	if(m_pMaster != NULL) {
		// 移除所有该类型的script对象
		UniqueManager::getInstance()->removeByType(UNIQUE_HANDLER_SCRIPT);
		m_pMaster->release();
		m_pMaster = NULL;
	}
}
void ScriptManager::timerUpdate(void){
	auto loopFunc = [](Unique* pUnique) {
		Script* pScript = (Script*)pUnique;
		TaskUpdate* pTask = new TaskUpdate(pScript);
		pTask->commitTask();
	};
	UniqueManager::getInstance()->loop(UNIQUE_HANDLER_SCRIPT, loopFunc);
}
static void mainTimerHandler(int signo){
	ScriptManager* pScriptManager = ScriptManager::getInstance();
	if( NULL != pScriptManager ){
		pScriptManager->timerUpdate();
	}
}
static void stopServiceUSR1(int signo){
    Epoll* pEpoll = Epoll::getInstance();
    fprintf(stderr, "stopServiceUSR1 called\n");
    if( NULL != pEpoll ){
        pEpoll->closeEpoll();
    }
}
bool ScriptManager::startTimer(unsigned int second, unsigned int nsecond){
    int status;
    struct sigaction act;
    struct itimerspec m_timerspec;
    struct sigevent m_sigevent;
    // 创建timer
    memset(&m_sigevent, 0, sizeof(struct sigevent));
    m_sigevent.sigev_signo = SIGALRM;
    m_sigevent.sigev_notify = SIGEV_SIGNAL;
    status = timer_create(CLOCK_REALTIME, &m_sigevent, &m_timer_id);
    if (status == -1){
        timer_delete(m_timer_id);
        perror("fail to timer_create");
        return false;
    }
    // 设置timer的时间间隔
    m_timerspec.it_value.tv_sec = second;
    m_timerspec.it_value.tv_nsec = nsecond;
    m_timerspec.it_interval.tv_sec = second;
    m_timerspec.it_interval.tv_nsec = nsecond;
    status = timer_settime(m_timer_id, 0, &m_timerspec, 0);
    if (status == -1){
        timer_delete(m_timer_id);
        perror("fail to timer_settime");
        return false;
    }
    //    这里需要设置信号监听函数
    memset(&act, 0, sizeof(act));
    act.sa_handler = mainTimerHandler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    if (sigaction(SIGALRM, &act, NULL) == -1){
        perror("fail to sigaction");
        timer_delete(m_timer_id);
        return false;
    }
    signal(SIGUSR1, stopServiceUSR1);
    return true;
}

NS_HIVENET_END
