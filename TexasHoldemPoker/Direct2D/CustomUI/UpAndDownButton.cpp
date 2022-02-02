#include "UpAndDownButton.h"

UpAndDownButton::UpAndDownButton()
{

}

UpAndDownButton::UpAndDownButton(const UpAndDownButton& other)
{

}

UpAndDownButton::~UpAndDownButton()
{

}

bool UpAndDownButton::InitializeEx(Direct2DEngine* D2DEngine, int x, int y, int width, int height, WCHAR* text)
{
	MainMenuButton::InitializeEx(D2DEngine, x, y, width, height, text);

	return true;
}

bool UpAndDownButton::Render()
{
	MainMenuButton::Render();
	return true;
}

bool UpAndDownButton::Release()
{
	MainMenuButton::Release();
	return true;
}