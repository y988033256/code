// GameCode.cpp		


#include "gamecode.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "myinputs.h"
#include <time.h>
#include "gametimer.h"
#include "errorlogger.h"
#include <math.h>
#include "shapes.h"
#include "spaceship.h"
#include "Rock.h"
#include "Bullet.h"
#include <list>
#include "Level.h"



Game::Game()
{

}

Game::~Game()
{
	// No-op
}

Game Game::instance;    // Singleton instance


ErrorType Game::Main()

{
	//Flip and clear the back buffer
	MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
	pTheDrawEngine->Flip();
	pTheDrawEngine->ClearBackBuffer();

	ErrorType err = SUCCESS;

	switch (m_currentState)
	{
	case MENU:
		err = MainMenu();     // Menu at start of game
		break;
	case PAUSED:
		err = PauseMenu();   // Player has paused the game
		break;
	case RUNNING:           // Playing the actual game
		err = Update();
		break;
	case LEADERBOARD:
		err = ShowLeaderboard();
		break;
	case WIN:
		err = ShowWinScreen();
		break;
	case ShowGameOverScreen:
		err = ShowGameOver();
		break;
	case Entername:
		err = PlayerName();
		break;
	case ENDOFGAME:
		err = FAILURE;      
	default:
	
		err = FAILURE;      
	}

	return err;


}
ErrorType Game::ShowWinScreen()
{
	int ScreenWidth = MyDrawEngine::GetInstance()->GetScreenWidth();
	int x = (ScreenWidth / 2) - 235;

	MyDrawEngine::GetInstance()->WriteText(x, 200, L"You Win !", MyDrawEngine::WHITE, 2);
	const int NUMOPTIONS = 4;
	wchar_t options[NUMOPTIONS][15] = { L"Main menu",L"Leaderboard",L"Play again", L"Quit" };

	for (int i = 0; i < NUMOPTIONS; i++)
	{
		int colour = MyDrawEngine::GREY;       // If not selected, should be grey
		if (i == m_menuOption)
		{
			colour = MyDrawEngine::WHITE;       // Current selection is white
		}
		MyDrawEngine::GetInstance()->WriteText(x, 450 + 80 * i, options[i], colour, 1);
	}

	MyInputs* pInputs = MyInputs::GetInstance();

	// Get user input
	pInputs->SampleKeyboard();

	// Move choice up and down
	if (pInputs->NewKeyPressed(DIK_UP))
	{
		m_menuOption--;
	}
	if (pInputs->NewKeyPressed(DIK_DOWN))
	{
		m_menuOption++;
	}
	if (m_menuOption < 0)
	{
		m_menuOption = 0;
	}
	else if (m_menuOption >= NUMOPTIONS)
	{
		m_menuOption = NUMOPTIONS - 1;
	}

	// If player chooses an option ....
	if (pInputs->NewKeyPressed(DIK_RETURN))
	{
		if (m_menuOption == 0)      // back to menu
		{
			ChangeState(MENU);  // Go back to running the game
		}
		if (m_menuOption == 1)      // play again
		{
			StartOfGame();
			ChangeState(LEADERBOARD);  // Go TO LEADERBOARD
		}
		if (m_menuOption == 2)      // play again
		{
			StartOfGame();
			ChangeState(RUNNING);  // Go back to running the game
		}
		if (m_menuOption == 3)      // Quit
		{
			EndOfGame();           // Clear up the game
			ChangeState(ENDOFGAME);     // Go back to the menu
		}

	}

	return SUCCESS;
}

void Game::AddLetter(wchar_t letter)
{
	
	int len = wcslen(username); 	// Get the current length of the text
	if (len > 20)
	{
		return;
	}
	username[len] = letter;
	username[len + 1] = '\0';
}
void Game::RemoveLetter()
{
	// Add code to check not exceeding 50 characters
	int len = wcslen(username); 	// Get the current length of the text
	if (len>0)
		username[len - 1] = '\0';
}
void Wchar_tToString(std::string& szDst, wchar_t *wchar)
{
	wchar_t * wText = wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);// WideCharToMultiByte的运用
	char *psText; // psText为char*的临时数组，作为赋值给std::string的中间变量
	psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);// WideCharToMultiByte的再次运用
	szDst = psText;// std::string赋值
	delete[]psText;// psText的清除
}


ErrorType Game::PlayerName()
{

	int ScreenWidth = MyDrawEngine::GetInstance()->GetScreenWidth();
	int ScreenHeight = MyDrawEngine::GetInstance()->GetScreenHeight();
	int x = (ScreenWidth / 2);
	int y = (ScreenHeight / 2);

	Rectangle2D R;
	R.PlaceAt(200, -300, 100, 300);
	MyDrawEngine::GetInstance()->FillRect(R, MyDrawEngine::WHITE);
	Rectangle2D R1;
	R1.PlaceAt(195, -295, 105, 295);
	MyDrawEngine::GetInstance()->FillRect(R1, MyDrawEngine::BLACK);


	MyDrawEngine::GetInstance()->WriteText(x - 130, 330, L"Enter your name", MyDrawEngine::WHITE, 3);

	MyDrawEngine::GetInstance()->WriteText(x - 130, 445, username, MyDrawEngine::WHITE);
	const int NUMOPTIONS = 3;
	wchar_t options[NUMOPTIONS][11] = { L"Yes", L"No", L"Quit" };

	for (int i = 0; i < NUMOPTIONS; i++)
	{
		int colour = MyDrawEngine::WHITE;       // If not selected, should be grey
		if (i == m_menuOption)
		{
			colour = MyDrawEngine::RED;       // Current selection is white
		}
		MyDrawEngine::GetInstance()->WriteText(x - 130 + 80 * i, 550, options[i], colour, 3);
	}

	MyInputs* pInputs = MyInputs::GetInstance();

	// Get user input
	pInputs->SampleKeyboard();
		if (pInputs->NewKeyPressed(DIK_A))
			AddLetter('a');
		if (pInputs->NewKeyPressed(DIK_B))
			AddLetter('b');
		if (pInputs->NewKeyPressed(DIK_C))
			AddLetter('c');
		if (pInputs->NewKeyPressed(DIK_D))
			AddLetter('d');
		if (pInputs->NewKeyPressed(DIK_E))
			AddLetter('e');
		if (pInputs->NewKeyPressed(DIK_F))
			AddLetter('f');
		if (pInputs->NewKeyPressed(DIK_G))
			AddLetter('g');
		if (pInputs->NewKeyPressed(DIK_H))
			AddLetter('h');
		if (pInputs->NewKeyPressed(DIK_I))
			AddLetter('i');
		if (pInputs->NewKeyPressed(DIK_J))
			AddLetter('j');
		if (pInputs->NewKeyPressed(DIK_K))
			AddLetter('k');
		if (pInputs->NewKeyPressed(DIK_L))
			AddLetter('l');
		if (pInputs->NewKeyPressed(DIK_M))
			AddLetter('m');
		if (pInputs->NewKeyPressed(DIK_N))
			AddLetter('n');
		if (pInputs->NewKeyPressed(DIK_O))
			AddLetter('o');
		if (pInputs->NewKeyPressed(DIK_P))
			AddLetter('p');
		if (pInputs->NewKeyPressed(DIK_Q))
			AddLetter('q');
		if (pInputs->NewKeyPressed(DIK_R))
			AddLetter('r');
		if (pInputs->NewKeyPressed(DIK_S))
			AddLetter('s');
		if (pInputs->NewKeyPressed(DIK_T))
			AddLetter('t');
		if (pInputs->NewKeyPressed(DIK_U))
			AddLetter('u');
		if (pInputs->NewKeyPressed(DIK_V))
			AddLetter('v');
		if (pInputs->NewKeyPressed(DIK_W))
			AddLetter('w');
		if (pInputs->NewKeyPressed(DIK_X))
			AddLetter('x');
		if (pInputs->NewKeyPressed(DIK_Y))
			AddLetter('y');
		if (pInputs->NewKeyPressed(DIK_Z))
			AddLetter('z');
		if (pInputs->NewKeyPressed(DIK_SPACE))
			AddLetter(' ');

	if (pInputs->NewKeyPressed(DIK_BACK))
	{
		RemoveLetter();
	}

	// Move choice up and down
	if (pInputs->NewKeyPressed(DIK_LEFT))
	{
		m_menuOption--;
	}
	if (pInputs->NewKeyPressed(DIK_RIGHT))
	{
		m_menuOption++;
	}

	if (m_menuOption < 0)
	{
		m_menuOption = 0;
	}
	else if (m_menuOption >= NUMOPTIONS)
	{
		m_menuOption = NUMOPTIONS - 1;
	}

	// If player chooses an option ....
	if (pInputs->NewKeyPressed(DIK_RETURN))
	{
		if (m_menuOption == 0)
		{
			if (wcslen(username) == 0)
			{
				ChangeState(Entername);
			}
			else
			{
				this->readPlayerRecord();
				Wchar_tToString(this->player.name, this->username);
				this->player.RecordScore = 0;
				this->player.rounds = 0;
				int count = this->players.size();
				count = count > 20 ? 20 : count;

				this->index = -1;      // - 1 说明 记录里没有此玩家
				for (int i = 0; i < count; i++)            // 循环查找次数 =  记录里面的 玩家数量    i 是位置  count 是数量
				{
					if (this->player.name == this->players[i].name)          //如果找到了此玩家名字
					{
						this->index = i;                                        //记录玩家在 记录中的位置 = i
						this->player.RecordScore = this->players[i].RecordScore;
						this->player.rounds = this->players[i].rounds;
						break;
					}
				}

				ChangeState(MENU);

			}// Go back to running the game
		}
		if (m_menuOption == 1)      // play again
		{
			StartOfGame();
			ChangeState(Entername);  // back to menu
			username[0] = '\0';
		}
		if (m_menuOption == 2)      // Quit
		{
			EndOfGame();           // Clear up the game
			ChangeState(ENDOFGAME);     // Go back to the menu
		}

	}


	return SUCCESS;
}
ErrorType Game::ShowGameOver()
{
	int ScreenWidth = MyDrawEngine::GetInstance()->GetScreenWidth();
	int x = (ScreenWidth / 2) - 235;

	MyDrawEngine::GetInstance()->WriteText(x, 200, L"Game Over !", MyDrawEngine::RED, 2);
	const int NUMOPTIONS = 4;
	wchar_t options[NUMOPTIONS][15] = { L"Main menu", L"Leaderboard", L"Play again", L"Quit" };

	for (int i = 0; i < NUMOPTIONS; i++)
	{
		int colour = MyDrawEngine::WHITE;       // If not selected, should be grey
		if (i == m_menuOption)
		{
			colour = MyDrawEngine::RED;       // Current selection is white
		}
		MyDrawEngine::GetInstance()->WriteText(x, 450 + 80 * i, options[i], colour, 1);
	}

	MyInputs* pInputs = MyInputs::GetInstance();

	// Get user input
	pInputs->SampleKeyboard();

	// Move choice up and down
	if (pInputs->NewKeyPressed(DIK_UP))
	{
		m_menuOption--;
	}
	if (pInputs->NewKeyPressed(DIK_DOWN))
	{
		m_menuOption++;
	}
	if (m_menuOption < 0)
	{
		m_menuOption = 0;
	}
	else if (m_menuOption >= NUMOPTIONS)
	{
		m_menuOption = NUMOPTIONS - 1;
	}

	// If player chooses an option ....
	if (pInputs->NewKeyPressed(DIK_RETURN))
	{
		if (m_menuOption == 0)      // back to menu
		{
			ChangeState(MENU);  // Go back to running the game
		}
		if (m_menuOption == 1)      // play again
		{
			ChangeState(LEADERBOARD);  // Go back to running the game
		}
		if (m_menuOption == 2)      // play again
		{
			StartOfGame();
			ChangeState(RUNNING);  // Go back to running the game
		}
		if (m_menuOption == 3)      // Quit
		{
			EndOfGame();           // Clear up the game
			ChangeState(ENDOFGAME);     // Go back to the menu
		}

	}

	return SUCCESS;
}

wchar_t* multiByteToWideChar(const string& pKey)
{
	const char*pCStrKey = pKey.c_str();
	//第一次调用返回转换后的字符串长度，用于确认为wchar_t*开辟多大的内存空间
	int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
	wchar_t *pWCStrKey = new wchar_t[pSize];
	//第二次调用将单字节字符串转换成双字节字符串
	MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);
	return pWCStrKey;
}

const wchar_t* RankNum[] =
{
	L"Rank 1", L"Rank 2", L"Rank 3", L"Rank 4", L"Rank 5",
	L"Rank 6", L"Rank 7", L"Rank 8", L"Rank 9", L"Rank 10",
	L"Rank 11", L"Rank 12", L"Rank 13", L"Rank 14", L"Rank 15",
	L"Rank 16", L"Rank 17", L"Rank 18", L"Rank 19", L"Rank 20",
};

void bubble_sort(structplayer* arrays, int size)
{
	structplayer temp;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (arrays[i].RecordScore > arrays[j].RecordScore)
			{
				temp = arrays[i];
				arrays[i] = arrays[j];
				arrays[j] = temp;
			}
		}
	}
}

ErrorType Game::ShowLeaderboard()
{
	int ScreenWidth = MyDrawEngine::GetInstance()->GetScreenWidth();
	int HalfScreenWidth = (ScreenWidth / 2);
	int x = HalfScreenWidth - 145;
	//	1920
	MyDrawEngine::GetInstance()->WriteText(x, 50, L"Leader Board", MyDrawEngine::WHITE, 1);
	//MyDrawEngine::GetInstance()->WriteText(HalfScreenWidth - 300, 100, L"W", MyDrawEngine::WHITE);
	//MyDrawEngine::GetInstance()->WriteText(HalfScreenWidth - 100, 100, L"N", MyDrawEngine::WHITE);
	//MyDrawEngine::GetInstance()->WriteText(HalfScreenWidth + 100, 100, L"N", MyDrawEngine::WHITE);
	//MyDrawEngine::GetInstance()->WriteText(HalfScreenWidth + 300, 100, L"F", MyDrawEngine::WHITE);

	int count = this->players.size();
	count = count > 20 ? 20 : count;

	structplayer* TempRecord = new structplayer[count];
	for (int i = 0; i < count; i++)
		TempRecord[i] = this->players[i];
	bubble_sort(TempRecord, count);

	for (int i = 0; i<count; i++)
	{
		int colour = MyDrawEngine::WHITE;


		//MyDrawEngine::GetInstance()->WriteText(850, 150 + 40 * i, names[i].c_str(), colour);
		// MyDrawEngine::GetInstance()->WriteInt(1000, 150 + 40 * i, scores[i], colour);
		MyDrawEngine::GetInstance()->WriteText(HalfScreenWidth - 325, 150 + 40 * i, RankNum[i], colour);

		wchar_t* name = multiByteToWideChar((string&)TempRecord[i].name);
		MyDrawEngine::GetInstance()->WriteText(HalfScreenWidth - 100, 150 + 40 * i, name, colour);
		MyDrawEngine::GetInstance()->WriteInt(HalfScreenWidth + 275, 150 + 40 * i, TempRecord[i].RecordScore, colour);

	}


	MyDrawEngine::GetInstance()->WriteText(800, 1000, L"Press Esc return to the menu", MyDrawEngine::WHITE);

	// Get keyboard input
	MyInputs* pInputs = MyInputs::GetInstance();

	pInputs->SampleKeyboard();
	if (pInputs->NewKeyPressed(DIK_ESCAPE))
	{
		ChangeState(MENU);
	}


	return SUCCESS;
}

// Use to change the state of the game. Private function
void Game::ChangeState(GameState newState)
{
	// Very crude state system
	// Close old state
	switch (m_currentState)
	{
	case MENU:
		// Not needed
		break;
	case PAUSED:
		// Not needed
		break;
	case RUNNING:
		// Not needed
		break;
	}

	// Change the state
	m_currentState = newState;
	m_menuOption = 0;

	// Transition to new state
	switch (m_currentState)
	{
	case MENU:
		// Not needed
		break;
	case PAUSED:
		// Not needed
		break;
	case RUNNING:
		// Not needed
		break;
	}
}


ErrorType Game::Setup(bool bFullScreen, HWND hwnd, HINSTANCE hinstance)
{
	// Create the engines - this should be done before creating other DDraw objects
	if (FAILED(MyDrawEngine::Start(hwnd, bFullScreen)))
	{
		ErrorLogger::Writeln(L"Failed to start MyDrawEngine");
		return FAILURE;
	}
	if (FAILED(MySoundEngine::Start(hwnd)))
	{
		ErrorLogger::Writeln(L"Failed to start MySoundEngine");
		return FAILURE;
	}
	if (FAILED(MyInputs::Start(hinstance, hwnd)))
	{
		ErrorLogger::Writeln(L"Failed to start MyInputs");
		return FAILURE;
	}
	return (SUCCESS);
}



// Terminates the game engines - Draw Engine, Sound Engine, Input Engine
// This is called just before the program exits
void Game::Shutdown()

{
	// Any clean up code here 






	// (engines must be terminated last)
	MyDrawEngine::Terminate();
	MySoundEngine::Terminate();
	MyInputs::Terminate();
}





ErrorType Game::PauseMenu()
{
	// Code for a basic pause menu

	MyDrawEngine::GetInstance()->WriteText(900, 300, L"Paused", MyDrawEngine::WHITE);

	const int NUMOPTIONS = 2;
	wchar_t options[NUMOPTIONS][11] = { L"Resume", L"Main menu" };

	// Display menu options
	for (int i = 0; i<NUMOPTIONS; i++)
	{
		int colour = MyDrawEngine::GREY;       // If not selected, should be grey
		if (i == m_menuOption)
		{
			colour = MyDrawEngine::WHITE;       // Current selection is white
		}
		MyDrawEngine::GetInstance()->WriteText(900, 400 + 50 * i, options[i], colour);
	}

	MyInputs* pInputs = MyInputs::GetInstance();

	// Get user input
	pInputs->SampleKeyboard();

	// Move choice up and down
	if (pInputs->NewKeyPressed(DIK_UP))
	{
		m_menuOption--;
	}
	if (pInputs->NewKeyPressed(DIK_DOWN))
	{
		m_menuOption++;
	}
	if (m_menuOption<0)
	{
		m_menuOption = 0;
	}
	else if (m_menuOption >= NUMOPTIONS)
	{
		m_menuOption = NUMOPTIONS - 1;
	}

	// If player chooses an option ....
	if (pInputs->NewKeyPressed(DIK_RETURN))
	{
		if (m_menuOption == 0)      // Resume
		{
			ChangeState(RUNNING);  // Go back to running the game
		}
		if (m_menuOption == 1)      // Quit
		{
			EndOfGame();           // Clear up the game
			ChangeState(MENU);     // Go back to the menu
		}

	}

	return SUCCESS;
}

// Called each frame when in the menu state. Manages the menu
// which is currently a basic placeholder
ErrorType Game::MainMenu()
{
	MyDrawEngine::GetInstance()->WriteText(900, 300, L"Main menu", MyDrawEngine::WHITE);

	const int NUMOPTIONS = 4;
	wchar_t options[NUMOPTIONS][18] = { L"Start game", L"Go Fullscreen", L"Leaderboard", L"Exit" };

	// If the window is currently fullscreen, change the second option to read "Go Windowed" instead
	if (MyDrawEngine::GetInstance()->IsWindowFullScreen())
	{
		wcscpy_s(options[1], 15, L"Go Windowed");
	}

	// Display the options
	for (int i = 0; i<NUMOPTIONS; i++)
	{
		int colour = MyDrawEngine::GREY;
		if (i == m_menuOption)
		{
			colour = MyDrawEngine::WHITE;
		}
		MyDrawEngine::GetInstance()->WriteText(900, 400 + 50 * i, options[i], colour);
	}
	/*
	for (int i = 0; i<10; i++)
	{
	int colour = MyDrawEngine::GREY;

	MyDrawEngine::GetInstance()->WriteInt(450, 450 + 50 * i, i*100, colour);
	MyDrawEngine::GetInstance()->WriteText(350, 450 + 50 * i,L"Player one", colour);
	}
	*/
	// Get keyboard input
	MyInputs* pInputs = MyInputs::GetInstance();

	pInputs->SampleKeyboard();
	if (pInputs->NewKeyPressed(DIK_UP))
	{
		m_menuOption--;
	}
	if (pInputs->NewKeyPressed(DIK_DOWN))
	{
		m_menuOption++;
	}
	if (m_menuOption<0)
	{
		m_menuOption = 0;
	}
	else if (m_menuOption >= NUMOPTIONS)
	{
		m_menuOption = NUMOPTIONS - 1;
	}

	// User selects an option
	if (pInputs->NewKeyPressed(DIK_RETURN))
	{
		if (m_menuOption == 0)          // Play
		{
			StartOfGame();             // Initialise the game
			ChangeState(RUNNING);      // Run it
		}

		if (m_menuOption == 1)          // Toggle full screen
		{
			if (MyDrawEngine::GetInstance()->IsWindowFullScreen())
			{
				MyDrawEngine::GetInstance()->GoWindowed();
			}
			else
			{
				MyDrawEngine::GetInstance()->GoFullScreen();
			}
		}
		if (m_menuOption == 2)          //Show leader board
		{
			ChangeState(LEADERBOARD);
		}

		if (m_menuOption == 3)          //Quit
		{
			ChangeState(ENDOFGAME);
		}
	}

	return SUCCESS;
}


// Called at the start of the game - when changing state from MENU to RUNNING
// Use this to initialise the core game
ErrorType Game::StartOfGame()
{
	ObjectManager::instance.DeleteAll();
	


	Level *pLevel = new Level();
	pLevel->Initialise();

	ObjectManager::instance.AddObject(pLevel, true);


	return SUCCESS;
}



// Called each frame when in the RUNNING state.
// Checks for user pressing escape (which puts the game in the PAUSED state)
// Flips and clears the back buffer
// Gameplay programmer will develop this to create an actual game
ErrorType Game::Update()
{
	theTimer.mark();
	ObjectManager::instance.UpdateAll(theTimer.mdFrameTime);
	ObjectManager::instance.RenderAll();

	ObjectManager::instance.DeleteInactive();

	ObjectManager::instance.CheckAllCollisions(theTimer.mdFrameTime);
	ObjectManager::instance.CheckBoundry();



	for (GameObject* pNextObject : ObjectManager::instance.getObject())
	{
		if (typeid(*pNextObject) == typeid(Level))
		{
			if (((Level*)pNextObject)->condition == 1)
			{
				int score = this->readScore();
				if (score>this->player.RecordScore)
					this->player.RecordScore = score;
				this->player.rounds += 1;

				this->writePlayerRecord();
				ChangeState(ShowGameOverScreen);
			}
			if (((Level*)pNextObject)->condition == 2)
			{
				int score = this->readScore();
				if (score>this->player.RecordScore)
					this->player.RecordScore = score;
				this->player.rounds += 1;
				this->writePlayerRecord();


				ChangeState(WIN);
			}

		}
	}




	// Check for entry to pause menu
	static bool escapepressed = true;
	if (KEYPRESSED(VK_ESCAPE))
	{
		if (!escapepressed)
			ChangeState(PAUSED);
		escapepressed = true;
	}
	else
		escapepressed = false;


	
	return SUCCESS;
}


ErrorType Game::EndOfGame()
// called when the game ends by returning to main menu
{
	
	ObjectManager::instance.DeleteAll();



	return SUCCESS;
}

void Game::readPlayerRecord(void)
{

	ifstream read("PlayerRecord.txt");
	while (true)
	{
		players.push_back(player);
		read >> players[players.size() - 1].name;
		read >> players[players.size() - 1].RecordScore;
		read >> players[players.size() - 1].rounds;
		if (read.eof())
		{
			players.pop_back();
			break;
		}
	}
	read.close();
}

void Game::writePlayerRecord(void)
{
	ofstream AllRecord;
	AllRecord.open("Records\\" + player.name + ".txt", std::ios::out | std::ios::app);

	if (this->index == -1)         //如果玩家不在记录中 index = -1 
	{
		players.push_back(player);       //创建玩家
		this->index = this->players.size() - 1;       //位置在player 列表的 最后面 （size-1）
	
		
	}
	else                             // 如果有这个玩家
	{
		this->players[index].RecordScore = this->player.RecordScore;      //成绩=成绩
		this->players[index].rounds = this->player.rounds;              //玩的次数 =玩的次数
	}
	ofstream write("PlayerRecord.txt");
	for (unsigned int i = 0; i < players.size(); i++)
	{
		write << players[i].name << " \t";
		write << players[i].RecordScore << " \t";
		write << players[i].rounds << " \t";
		write << endl;
	}

	write.flush();
	write.close();

	AllRecord << player.RecordScore << " \t";
	AllRecord << endl;

	AllRecord.flush();
	AllRecord.close();

}

int Game::readScore(void)
{
	for (GameObject* pNextObject : ObjectManager::instance.getObject())
	{
		if (typeid(*pNextObject) == typeid(Level))
			return ((Level*)pNextObject)->score;
	}
}
