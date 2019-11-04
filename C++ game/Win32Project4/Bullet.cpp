#include "Bullet.h"


void Bullet::Initialise(Vector2D position, float angle)        // initialise the Bullet give the postion and angle of the spaceship
{
	int Bulletspeed = 1000;                                        // bullet travel speed
	active = true;
	this->position = position;
	this->angle = angle;
	velocity.setBearing(angle, Bulletspeed);
	scale = 6.0f;													// allow me to contorl the size of the bullet
	timer = 2.0f;                                            // give the shoot timer , allow to shoot a bullet every 2 second


	picture = MyDrawEngine::GetInstance()->LoadPicture(L"bullet.bmp");          // pre load the image
}

Bullet::Bullet()
{
	active = false;
}

void Bullet::Update(double fps)				// update the Bullet every FPS
{
	timer = timer - fps;
	if (timer < 0)                              // if shoot time < 0 second , player allow to shoot 
	{
		active = false;
	}
	position = position + velocity*float(fps);
	collisionshape.PlaceAt(position,2);
}

IShape2D* Bullet::GetShape()
{
	return &collisionshape;
}

void Bullet::ProcessCollision(GameObject* pOther, double fps)      // when Bullet collide with something it will process here
{
	active = false;
	Explosion* pExp = new Explosion();
	pExp->Initialise(position);
	ObjectManager::instance.AddObject(pExp, true);	
}
