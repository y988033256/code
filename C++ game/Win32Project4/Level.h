#pragma once

#include "vector2D.h"
#include "GameObject.h"
#include "mydrawengine.h"
#include "spaceship.h"
#include <time.h>

using namespace std;

class Level :public GameObject    //create a Level class which inherit gameobject 
{
private:
	int numRock;
	Spaceship *pSpaceship;
	
	
public:
	int score;
	time_t old;  
	time_t now;
	double  ca = 0;
	double CD = 60;
	int m;
	int s;
	int condition;
	Level();
	static Level instance;
	void Render();
	void Initialise();
	void Update(double fps);
	IShape2D* GetShape();
	void ProcessCollision(GameObject* pOther, double fps);
	int getnumRock();
	void Addscore(int amount);
	
};

