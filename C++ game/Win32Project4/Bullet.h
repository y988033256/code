#pragma once
#include "vector2D.h"
#include "GameObject.h"
#include "mydrawengine.h"
#include "Explosion.h"
#include "ObjectManager.h"
using namespace std;

class Bullet :public GameObject   //create a Bullet class which inherit gameobject 
{
private:
	float timer;


public:
	IShape2D* GetShape();
	Bullet();
	void Initialise(Vector2D position, float angle);
	void Update(double fps);
	void ProcessCollision(GameObject* pOther, double fps);

};