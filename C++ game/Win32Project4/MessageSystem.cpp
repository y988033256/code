#include "MessageSystem.h"
#include "Level.h"
#include "ObjectManager.h"

MessageSystem::MessageSystem()
{

	messagetype[0] = "UPDATE_SCORE";
	messagetype[1] = "REDUCE_HP";
	messagetype[2] = "EXPLOSION";
}

MessageSystem MessageSystem::instance;



void MessageSystem::ProcessMessages(string messagetype)
{
	if (!messagetype.compare("UPDATE_SCORE"))
	{
	
		for (GameObject* pNextObject : ObjectManager::instance.getObject())
		{
			if (typeid(*pNextObject) == typeid(Level))
				((Level*)pNextObject)->Addscore(10);
		}
  		
	}

/*
	if (!messagetype.compare("REDUCE_HP"))
	{

		for (GameObject* pNextObject : ObjectManager::instance.getObject())
		{
			if (typeid(*pNextObject) == typeid(Spaceship))
			((Spaceship*)pNextObject)->setHealth(-1);
		}

	}
	*/

	/*
	if (!messagetype.compare("EXPLOSION"))
	{
		for (GameObject* pNextObject : ObjectManager::instance.getObject())
		{
			if (typeid(*pNextObject) == typeid(Bullet)&& ((Bullet*)pNextObject)->hit == true )
				((Bullet*)pNextObject)->Bum();
		}
		
	}
	*/
}