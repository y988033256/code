#pragma once
#include "vector2D.h"
#include "GameObject.h"
#include "mydrawengine.h"
#include "shapes.h"
#include "Level.h"


using namespace std;

class Rock :public GameObject    //create a Rock class which inherit gameobject 
{
private:
	
	int hp;
public:
	int collisionsize;
	Rock();
	void Initialise();
	void Update(double fps);
	void ProcessCollision(GameObject* pOther, double fps);
	IShape2D* GetShape();

};
