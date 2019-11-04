#include "Explosion.h"
#include "mysoundengine.h"
using namespace std;


Explosion::Explosion()    //  Constructor of Explosion
{
	active = false;
}



void Explosion::Initialise(Vector2D position)   // initialise the Explosion
{
	active = true;						// set it active
	currentimage = 0;
	this->position = position;				// give it the position of the  previous object

	image[0] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion1.bmp");          // pre load all the explosion image , to create the explosion anmimation 
	image[1] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion2.bmp");
	image[2] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion3.bmp");
	image[3] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion4.bmp");
	image[4] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion5.bmp");
	image[5] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion6.bmp");
	image[6] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion7.bmp");
	image[7] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion8.bmp");

	explosionSound[0] = MySoundEngine::GetInstance()->LoadWav(L"explosion.wav");   // pre load all the explosion sound
	explosionSound[1] = MySoundEngine::GetInstance()->LoadWav(L"explosion1.wav");
	explosionSound[2] = MySoundEngine::GetInstance()->LoadWav(L"explosion2.wav");
	explosionSound[3] = MySoundEngine::GetInstance()->LoadWav(L"explosion3.wav");
	explosionSound[4] = MySoundEngine::GetInstance()->LoadWav(L"explosion4.wav");
	explosionSound[5] = MySoundEngine::GetInstance()->LoadWav(L"explosion5.wav");

	int r = rand() % 5;     // create the random number 
	MySoundEngine* pSE = MySoundEngine::GetInstance();
	pSE->Play(explosionSound[r], false);
}

void Explosion::Update(double fps)		// update the Explosion every FPS
{
	currentimage = currentimage + 5 * fps;
	if (currentimage >= 8)
	{
		active = false;
	}
}
IShape2D* Explosion::GetShape()
{
	return &collisionshape;
}
void Explosion::ProcessCollision(GameObject* pOther, double fps)
{
}
void Explosion::Render()   // explosion have a unique render function
{
	if (active == true)
	{
		MyDrawEngine::GetInstance()->DrawAt(position, image[int(currentimage)], scale, angle, 0.0f);
	}
}

