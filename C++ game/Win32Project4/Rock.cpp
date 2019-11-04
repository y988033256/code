#include "Rock.h"
#include "spaceship.h"
#include "Bullet.h"
#include "Level.h"




Rock::Rock()  //  Constructor of Rock
{
	hp = 4;
	active = false;
}

void Rock::Initialise()   // initialise the Rock
{
	active = true;			// set it active
	float angle = rand() % 628 / 100.0f;              // this will prevent rocks appearing in the center 
	float distant = rand() % 1300 + 300.0f;			// this will prevent rocks appearing in the center 
	
	position.setBearing(angle, distant);
	
	collisionshape.PlaceAt(position, 50);		// place the shape allow to check collision later

	velocity.set(rand() % 6 - 2.5, rand() % 6 - 2.5);         // give a random movement speed


	int r = rand() % 4;                  // give a random number so rock will have a random pitcure
	if (r == 0)
	{
		picture = MyDrawEngine::GetInstance()->LoadPicture(L"rock1.bmp");
	}
	if (r == 1)
	{
		picture = MyDrawEngine::GetInstance()->LoadPicture(L"rock2.bmp");
	}
	if (r == 2)
	{
		picture = MyDrawEngine::GetInstance()->LoadPicture(L"rock3.bmp");
	}
	if (r == 3)
	{
		picture = MyDrawEngine::GetInstance()->LoadPicture(L"rock4.bmp");
	}


}

void Rock::Update(double fps)   // update the Rock every FPS
{
	position = position + velocity;       // movement of the rock
	collisionshape.PlaceAt(position, 50); // place the shape allow to check collision later
}

IShape2D* Rock::GetShape()
{
	return &collisionshape;
}

void Rock::ProcessCollision(GameObject* pOther, double fps)			// when Rock collide with something it will process here
{
	if (typeid(*pOther) == typeid(Bullet))                     // everytime Bullet hit the rock , rock will - 1 hp
	{
		hp -= 1;
		if (hp <= 0)                                            // when rock hp <=0  
		{
			active = false;                                   // rock set to inactive
			for (GameObject* pNextObject : ObjectManager::instance.getObject())
			{
				if (typeid(*pNextObject) == typeid(Level))
					((Level*)pNextObject)->Addscore(10);
			}

			hp = 4;															//set hp back to 4 
		}
	}
}
