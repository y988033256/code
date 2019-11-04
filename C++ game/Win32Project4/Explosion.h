#pragma once
#include "vector2D.h"
#include "mydrawengine.h"
#include "GameObject.h"

using namespace std;



class Explosion :public GameObject    //create a Explosion class which inherit gameobject 
{
	float currentimage;
	PictureIndex image[8];
	SoundIndex explosionSound[6];
public:
	Explosion();
	void Initialise(Vector2D position);
	void Update(double fps);
	void Render();
	IShape2D* GetShape();
	void ProcessCollision(GameObject* pOther, double fps);
};
