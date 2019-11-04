
#pragma once
#include "errortype.h"
#include "windows.h"
#include "mydrawengine.h"
#include "gametimer.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include <string>
#include "InputBox.h"
#include <fstream>
#include <stdio.h>
#include <tchar.h>
#include <vector>

//#include <list>
using namespace std;

typedef struct
{
	string name;
	int RecordScore;
	int rounds;
} structplayer;



#define KEYPRESSED(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)


class Game
{
private:
	GameTimer theTimer;
	SoundIndex shootSound;
	//int scores[10];
    //std::wstring names[10];
	wchar_t username[50];
	void AddLetter(wchar_t);
	void RemoveLetter();
	enum GameState{ MENU, PAUSED, RUNNING, LEADERBOARD, ShowGameOverScreen, WIN, ENDOFGAME , Entername };
	GameState m_currentState = Entername;      // Current state of the game 
                                  // Menu = start menu
                                  // Paused = paused
                                  // Running = the main game loop
                                  // GAMEOVER = setting this state causes the program to close
                                  //            after tidying up
	void ChangeState(GameState newState);  // Use to change the state of the game to one of the states above
	
	GameObject* pTheSpaceShip;          // Pointer to superclass!
	
	int m_menuOption;              // Tracks the currently selected menu option, during main or pause menu
	Game();                        // Constructor
	~Game();                       // Destructor
	Game(Game& other);             // Copy constructor disabled

public:
	int index;
	vector<structplayer> players;
	structplayer player;
	void readPlayerRecord(void);
	void writePlayerRecord(void);
	int readScore(void);

	//void AddScore(wstring name, int score); do this later

	//void AddObject(GameObject* pNewObject, bool front);
	static Game instance;          // Singleton instance

   // Starts the game engines - Draw Engine, Sound Engine, Input Engine - singletons
   // This is called soon after the program runs
	ErrorType Setup(bool bFullScreen, HWND hwnd, HINSTANCE hinstance);

   // Terminates the game engines - Draw Engine, Sound Engine, Input Engine
   // This is called just before the program exits
	void Shutdown();


	
   // This is repeated, called every frame.
   // It will run either Update( ), MainMenu() or PauseMenu() depending on the
   // game state
	ErrorType Main();

   // Called each frame when in the pause state. Manages the pause menu
   // which is currently a basic placeholder
	ErrorType PauseMenu();

   // Called each frame when in the menu state. Manages the main menu,
   // which is currently a basic placeholder.
	ErrorType MainMenu();
	ErrorType PlayerName();
	ErrorType ShowLeaderboard();
	ErrorType ShowWinScreen();
	ErrorType ShowGameOver();
   // Called at the start of the game - when changing state from MENU to RUNNING
   // Use this to initialise the core game
	ErrorType StartOfGame();

   // Called each frame when in the RUNNING state.
   // Checks for user pressing escape (which puts the game in the PAUSED state)
   // Flips and clears the back buffer
   // Gameplay programmer will develop this to create an actual game
	ErrorType Update();

   // Called when the player ends the game
   // Currently this is done from the PAUSED state, when returning to the main menu
   // but could be done by the gameplay programmer in other situations
   // This will be used by the gameplay programmer to clean up
	ErrorType EndOfGame();
};




