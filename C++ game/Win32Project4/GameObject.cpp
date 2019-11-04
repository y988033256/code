#include "GameObject.h"

void GameObject::Render()           // give game object a draw function
{
	if (active == true){
		MyDrawEngine::GetInstance()->DrawAt(position, picture, scale, angle, 0.0f);
	}
}
GameObject:: ~GameObject()
{
}
GameObject::GameObject()
{
}
bool GameObject::IsActive()
{
	return active;
}

Vector2D GameObject::getposition()
{
	return position;
}

void GameObject::setactive(bool objectactive)
{
	active = objectactive;
}

void GameObject::setposition()
{
	position.set(0, 0);
}
