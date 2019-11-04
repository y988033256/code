#pragma once
#include "vector2D.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include<string>
#include <iostream>
#include "shapes.h"



using namespace std;


class GameObject            // the super class of all the game object 
{
protected:
	Vector2D velocity;
	Circle2D collisionshape;
	Vector2D position;
	float angle;
	bool active;
	float scale = 1.0f;
	PictureIndex picture;
	void Loadimage(string filename);
	//Vector2D startpoint.set(0,0)


public:
	GameObject();
	virtual ~GameObject();
	virtual void Render();
	virtual void Update(double fps) = 0;
	bool IsActive();
	virtual IShape2D* GetShape() = 0;
	virtual void ProcessCollision(GameObject* pOther, double fps) = 0;
	virtual Vector2D getposition();
	void setactive(bool objectactive);
	void setposition();
};
