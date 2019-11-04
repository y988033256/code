#pragma once
#include <list>
#include "GameObject.h"

using namespace std;

class ObjectManager                       // a clase can manage all the object 
{
private:

	list<GameObject *> pobjects;

public:                                 
	ObjectManager();

	static ObjectManager instance;

	void AddObject(GameObject* pNewObject, bool front);
	void UpdateAll(double fps);
	void RenderAll();
	void DeleteAll();
	void DeleteInactive();
	void CheckAllCollisions(double fps);
	void CheckBoundry();
	int countrocks();
	list<GameObject *> getObject();
};

