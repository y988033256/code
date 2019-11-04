#include "InputBox.h"
#include "mydrawengine.h"

void InputBox::Render()
{
	int ScreenWidth = MyDrawEngine::GetInstance()->GetScreenWidth();
	int x = (ScreenWidth / 2);

}

void InputBox::Update(double fps)
{
	MyInputs* pInput = MyInputs::GetInstance();

	pInput->SampleKeyboard();

	if (pInput->NewKeyPressed(DIK_A))
		AddLetter('a');
	if (pInput->NewKeyPressed(DIK_B))
		AddLetter('b');
	if (pInput->NewKeyPressed(DIK_C))
		AddLetter('c');
	if (pInput->NewKeyPressed(DIK_D))
		AddLetter('d');
	if (pInput->NewKeyPressed(DIK_E))
		AddLetter('e');
	if (pInput->NewKeyPressed(DIK_F))
		AddLetter('f');
	if (pInput->NewKeyPressed(DIK_G))
		AddLetter('g');
	if (pInput->NewKeyPressed(DIK_H))
		AddLetter('h');
	if (pInput->NewKeyPressed(DIK_I))
		AddLetter('i');
	if (pInput->NewKeyPressed(DIK_J))
		AddLetter('j');
	if (pInput->NewKeyPressed(DIK_K))
		AddLetter('k');
	if (pInput->NewKeyPressed(DIK_L))
		AddLetter('l');
	if (pInput->NewKeyPressed(DIK_M))
		AddLetter('m');
	if (pInput->NewKeyPressed(DIK_N))
		AddLetter('n');
	if (pInput->NewKeyPressed(DIK_O))
		AddLetter('o');
	if (pInput->NewKeyPressed(DIK_P))
		AddLetter('p');
	if (pInput->NewKeyPressed(DIK_Q))
		AddLetter('q');
	if (pInput->NewKeyPressed(DIK_R))
		AddLetter('r');
	if (pInput->NewKeyPressed(DIK_S))
		AddLetter('s');
	if (pInput->NewKeyPressed(DIK_T))
		AddLetter('t');
	if (pInput->NewKeyPressed(DIK_U))
		AddLetter('u');
	if (pInput->NewKeyPressed(DIK_V))
		AddLetter('v');
	if (pInput->NewKeyPressed(DIK_W))
		AddLetter('w');
	if (pInput->NewKeyPressed(DIK_X))
		AddLetter('x');
	if (pInput->NewKeyPressed(DIK_Y))
		AddLetter('y');
	if (pInput->NewKeyPressed(DIK_Z))
		AddLetter('z');
}

void InputBox::AddLetter(wchar_t letter)
{
	// Add code to check not exceeding 50 characters
	int len = wcslen(PlayerName); 	// Get the current length of the text
	PlayerName[len] = letter;
	PlayerName[len + 1] = '\0';
}

IShape2D* InputBox::GetShape()
{
	return &collisionshape;
}
void InputBox::ProcessCollision(GameObject* pOther, double fps){
}
