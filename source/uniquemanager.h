//
// Created by IntelliJ IDEA.
// User: AppleTree
// Date: 16/6/9
// Time: 下午10:28
// To change this template use File | Settings | File Templates.
//

#ifndef __hivenet__uniquemanager__
#define __hivenet__uniquemanager__

#include "common.h"

NS_HIVENET_BEGIN

class UniqueManager : public RefObject, public Sync
{
public:
	typedef Unique*(*CreateFunction)(unique_char uniqueType);
	typedef std::vector<Unique*> UniqueVector;
	typedef std::vector<unique_int> IntVector;
	typedef std::vector<IntVector> IdleVector;
	typedef std::vector<CreateFunction> CreateFunctionVector;
public:
	UniqueManager(void);
	virtual ~UniqueManager(void);

	static UniqueManager* getInstance(void);
	static UniqueManager* createInstance(void);
	static void destroyInstance(void);

	void registerCreateFunction(unique_char uniqueType, CreateFunction func);
	Unique* create(unique_char uniqueType);
	Unique* getByHandle(unique_long handle);
	void idle(Unique* pUnique);
	void idle(unique_long handle);
	void remove(Unique* pUnique);
	void remove(unique_long handle);
	void removeByType(unique_char uniqueType);
protected:
	void releaseObjects(void);
protected:
	UniqueVector m_uniqueObjects;
	IdleVector m_idleIndex;
	CreateFunctionVector m_createFunctions;
};

NS_HIVENET_END

#endif
