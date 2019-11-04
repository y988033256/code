#include "vector2D.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "shapes.h"
#pragma once
class Spaceship :public GameObject        //create a spaceship class which inherit gameobject 
{
private:
	Vector2D front;
	double shootDelayTimer;
	double CollisionDelayTimer;
	SoundIndex shootSound;
	int Health;
public:
	IShape2D* GetShape();
	void ProcessCollision(GameObject* pOther, double fps);
	Spaceship();
	void Initialise();
	void Update(double fps);
	int getHealth();
	void setactive(bool a);
	void setHealth(int health);
	

};
