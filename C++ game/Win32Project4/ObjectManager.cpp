#include "ObjectManager.h"
#include "gametimer.h"
#include <algorithm>
#include "mydrawengine.h"
#include "Rock.h"


using namespace std;


ObjectManager::ObjectManager()    //Constructor of ObjectManager
{

}

ObjectManager ObjectManager::instance;

void ObjectManager::AddObject(GameObject* pNewObject, bool front)              // allow the object manage to add all the object into a the list, it can be added infront of the list or the back of the list 
{
	if (front == true){
		pobjects.push_back(pNewObject);
	}
	else
	{
		pobjects.insert(pobjects.begin(), pNewObject);
	}
}
void ObjectManager::UpdateAll(double fps)            //  allow the object manage to update all the object 
{
	for (GameObject* pnextObeject : pobjects)
	{
		pnextObeject->Update(fps);
	}
}
void ObjectManager::RenderAll()	//  allow the object manage to render all the object 
{
	for (GameObject* pnextObeject : pobjects)
	{
		pnextObeject->Render();
	}
}
void ObjectManager::DeleteAll()		//  allow the object manage to delete all the object 
{
	for (GameObject* pnextObeject : pobjects)
	{
		if (pnextObeject)
			delete pnextObeject;
	}
	pobjects.clear();
}
void ObjectManager::DeleteInactive()	//  allow the object manage to delete inactive object 
{
	for (GameObject* &nextObjectPointer : pobjects)
	{
		if (nextObjectPointer && nextObjectPointer->IsActive() == false)
		{
			delete nextObjectPointer;
			nextObjectPointer = nullptr;
		}
	}
	auto it = std::remove(pobjects.begin(), pobjects.end(), nullptr);
	pobjects.erase(it, pobjects.end());
}





void ObjectManager::CheckAllCollisions(double fps){              //  allow the object manage to check all the object if they are collide with each other 

	list<GameObject*>::iterator it1;
	list<GameObject*>::iterator it2;

	for (it1 = pobjects.begin(); it1 != pobjects.end(); it1++)
	{
		for (it2 = next(it1); it2 != pobjects.end(); it2++)
		{
			if ((*it1)->IsActive() && (*it2)->IsActive() && (*it1)->GetShape()->Intersects(*((*it2)->GetShape())))

			{
				(*it1)->ProcessCollision((*it2), fps);
				(*it2)->ProcessCollision((*it1), fps);
			}
		}
	}

}

void ObjectManager::CheckBoundry()			// allow the object manage to check all the object if they are outside of the screen
{
	list<GameObject*>::iterator it1;
	
	for (it1 = pobjects.begin(); it1 != pobjects.end(); it1++)
	{
		if (typeid(*(*it1)) != typeid(Spaceship))
		{
			if ((*it1)->getposition().XValue > MyDrawEngine::GetInstance()->GetScreenWidth() || (*it1)->getposition().YValue > MyDrawEngine::GetInstance()->GetScreenHeight())
			{

				(*it1)->setactive(false);
			}
			if ((*it1)->getposition().XValue < -MyDrawEngine::GetInstance()->GetScreenWidth() || (*it1)->getposition().YValue < -MyDrawEngine::GetInstance()->GetScreenHeight())
			{
				(*it1)->setactive(false);
			}
		}
	}

	list<GameObject*>::iterator it2;
	for (it2 = pobjects.begin(); it2 != pobjects.end(); it2++)
	{
		if (typeid(*(*it2)) == typeid(Spaceship))
		{
			if ((*it2)->getposition().XValue > MyDrawEngine::GetInstance()->GetScreenWidth() || (*it2)->getposition().YValue > MyDrawEngine::GetInstance()->GetScreenHeight())
			{

				(*it2)->setposition();
			}
			if ((*it2)->getposition().XValue < -MyDrawEngine::GetInstance()->GetScreenWidth() || (*it2)->getposition().YValue < -MyDrawEngine::GetInstance()->GetScreenHeight())
			{
				(*it2)->setposition();
			}
		}
	}






}

int ObjectManager::countrocks()             // count the number of the rock in the game have left 
{
	list<GameObject*>::iterator it1;
	int count = 0;
	for (GameObject* pNextObject : pobjects)
	{
		if (typeid(*pNextObject) == typeid(Rock))
			count++;

	}
	return count;
}

list<GameObject *> ObjectManager::getObject()
{
	return pobjects;
}