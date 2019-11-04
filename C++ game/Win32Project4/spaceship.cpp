#include "spaceship.h"
#include "myinputs.h"
#include "mysoundengine.h"
#include "gamecode.h"
#include "Bullet.h"
#include "ObjectManager.h"
#include <list>
#include "rock.h"
using namespace std;


Spaceship::Spaceship()   //  Constructor of Spaceship 
{
	active = false;
}

void Spaceship::Initialise()   // initialise the spaceship
{
	active = true;				// set it active
	Health = 10;                 // give it 10 hp

	velocity.set(0, 0);
	position.set(0, 0);            // spaceship start point is mid
	angle = 0;
	picture = MyDrawEngine::GetInstance()->LoadPicture(L"basic.bmp");           // preload picture 
	shootSound = MySoundEngine::GetInstance()->LoadWav(L"shoot.wav");         // preload sound 

}
void Spaceship::Update(double fps)          // update the spaceship every FPS
{
	if (active == true)                 // if spaceship is active do something
	{
		MyInputs* pInputs = MyInputs::GetInstance();        // allow keyboard input
		pInputs->SampleKeyboard();

		MySoundEngine* pSE = MySoundEngine::GetInstance();


		Vector2D acceleration;

		//spaceship shoot function
		shootDelayTimer = shootDelayTimer - fps;
		if (pInputs->KeyPressed(DIK_SPACE) && shootDelayTimer <= 0)
		{

			// Vector2D Bullet_velocity;
			Vector2D bulletPosition = front + position;

			Bullet *pBullet = new Bullet();
			pBullet->Initialise(bulletPosition, angle);

			ObjectManager::instance.AddObject(pBullet, true);
			front.setBearing(angle, 55.0f);
			shootDelayTimer = 0.2f;
		}

		// spaceship movement
		if (pInputs->KeyPressed(DIK_LEFT))
		{
			angle -= 0.04f;
		}
		if (pInputs->KeyPressed(DIK_RIGHT))
		{
			angle += 0.04f;
		}

		if (pInputs->KeyPressed(DIK_UP))
		{
			acceleration.setBearing(angle, 400);

		}
		else
		{
			Vector2D friction = -1.25 * velocity;
			velocity = velocity + friction*float(fps);
		}

		if (pInputs->KeyPressed(DIK_DOWN))
		{
			acceleration.setBearing(angle, -400);
		}

		if (pInputs->KeyPressed(DIK_SPACE))
		{
			pSE->Play(shootSound, false);

		}




		velocity = velocity + acceleration*float(fps);
		position = position + velocity*float(fps);
	}
	collisionshape.PlaceAt(position, 50);     // place the shape allow to check collision later
}

IShape2D* Spaceship::GetShape()
{
	return &collisionshape;
}


void Spaceship::ProcessCollision(GameObject* pOther, double fps)            // when spaceship collide with something it will process here
{
	CollisionDelayTimer = CollisionDelayTimer - fps;
	if (typeid(*pOther) == typeid(Rock) && CollisionDelayTimer <= 0){

		Health -= 1;
		CollisionDelayTimer = 2.0f;     
		
	}
}

int Spaceship::getHealth()
{
	return Health;
}

void Spaceship::setHealth(int health)
{
	Health += health;
}


void Spaceship::setactive(bool a)
{
	active = a;
}


