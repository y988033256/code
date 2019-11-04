#include "Level.h"
#include "Rock.h"
#include "ObjectManager.h"



Level Level::instance;

Level::Level()
{
}


void Level::Initialise()                       // initialise the level
{
	m = (int)CD / 60;
	s = (int)CD % 60;
	time(&old);
	pSpaceship = new Spaceship();               // create the space ship
	pSpaceship->Initialise();              // initialise it 

	ObjectManager::instance.AddObject(pSpaceship, true);      // add the spaceship in the object list 

	active = true;									//set spaceship active
							
}

void Level::Update(double fps)            // update the spaceship every FPS
{
	time(&now);
	ca = difftime(now, old);
	if (ca >= 1)
	{
		old = now;
		ca = 0;
		CD--;
		m = (int)CD / 60;
		s = (int)CD % 60;
	}

	if (ObjectManager::instance.countrocks() <= 60)      // if the rock is <= 60  , then create more  rock for player 
	{
		int r = rand() % 15;
		for (int i = 1; i < r; i++)
		{
			Rock *Tempprock = new Rock();
			Tempprock->Initialise();
			ObjectManager::instance.AddObject(Tempprock, false);
		}
	}
	if ( pSpaceship && pSpaceship->getHealth() <= 0 )          // if space ship hp is <= 0 ,set it inactive and remove it
	{
		pSpaceship->setactive(false);
		pSpaceship = nullptr;
		condition = 1;
	}
	
	if (CD <= 0)
	{
		condition = 2;
	} 

}

void Level::Render()                                    // display the socre, hp , and number of targets 
{
	Rectangle2D R;
	R.PlaceAt(1000, 1300, 670, 1760);
	Rectangle2D R2;
	R2.PlaceAt(998, 1302, 918, 1757);
	Rectangle2D R3;
	R3.PlaceAt(916, 1302, 836, 1757);
	Rectangle2D R4;
	R4.PlaceAt(834, 1302, 754, 1757);
	Rectangle2D R5;
	R5.PlaceAt(752, 1302, 672, 1757);
	
	MyDrawEngine::GetInstance()->FillRect(R, MyDrawEngine::WHITE);
	MyDrawEngine::GetInstance()->FillRect(R2, MyDrawEngine::BLACK);
	MyDrawEngine::GetInstance()->FillRect(R3, MyDrawEngine::BLACK);
	MyDrawEngine::GetInstance()->FillRect(R4, MyDrawEngine::BLACK);
	MyDrawEngine::GetInstance()->FillRect(R5, MyDrawEngine::BLACK);

	MyDrawEngine::GetInstance()->WriteText(Vector2D(1320, 980), L"Score :", MyDrawEngine::WHITE);
	MyDrawEngine::GetInstance()->WriteInt(Vector2D(1550, 980), score, MyDrawEngine::WHITE);

	MyDrawEngine::GetInstance()->WriteText(Vector2D(1320, 900), L"Targets :", MyDrawEngine::WHITE);
	MyDrawEngine::GetInstance()->WriteInt(Vector2D(1550, 900), ObjectManager::instance.countrocks(), MyDrawEngine::WHITE);

	if (pSpaceship == nullptr || pSpaceship->getHealth() == 0)                  //if space ship hp == 0 its dead display message : Spaceship is dead!
	{
		MyDrawEngine::GetInstance()->WriteText(Vector2D(1320, 820), L"Spaceship is dead!", MyDrawEngine::RED);
	}
	else
	{
		MyDrawEngine::GetInstance()->WriteText(Vector2D(1320, 820), L"HP :", MyDrawEngine::WHITE);
		MyDrawEngine::GetInstance()->WriteInt(Vector2D(1550, 820), pSpaceship->getHealth(), MyDrawEngine::WHITE);
	}

	MyDrawEngine::GetInstance()->WriteText(Vector2D(1320, 740), L"Time :", MyDrawEngine::WHITE);
	MyDrawEngine::GetInstance()->WriteInt(Vector2D(1550, 740), m, MyDrawEngine::WHITE);	
	MyDrawEngine::GetInstance()->WriteText(Vector2D(1550, 745), L" :", MyDrawEngine::WHITE);
	MyDrawEngine::GetInstance()->WriteInt(Vector2D(1600, 740), s, MyDrawEngine::WHITE);
}
IShape2D* Level::GetShape()  
{
	return &collisionshape;  
}
void Level::ProcessCollision(GameObject* pOther, double fps){
}
int Level::getnumRock()
{
	return numRock;
}
void Level::Addscore(int amount)
{
	score = score + amount;

}
