#pragma once
#include "GameObject.h"
#include "myinputs.h"

using namespace std;

class InputBox : public GameObject
{
	wchar_t PlayerName[50];
	void AddLetter(wchar_t);                   // Adds a letter to the string
	Circle2D collisionshape;
public:
	void Render();
	void Update(double fps);
	void ProcessCollision(GameObject* pOther, double fps);
	IShape2D* GetShape();

};