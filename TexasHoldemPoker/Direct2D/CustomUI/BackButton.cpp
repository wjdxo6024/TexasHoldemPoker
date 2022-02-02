#include "BackButton.h"

BackButton::BackButton()
{

}

BackButton::BackButton(const BackButton& other)
{

}

BackButton::~BackButton()
{

}

bool BackButton::InitializeEx(Direct2DEngine* D2DEngine, int x, int y, int width, int height, WCHAR* text)
{
	return true;
}

bool BackButton::Render()
{
	MainMenuButton::Render();
	return true;
}

bool BackButton::Release()
{
	MainMenuButton::Release();
	return true;
}