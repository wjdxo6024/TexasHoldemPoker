#pragma once
#include "MainMenuButton.h"
class UpAndDownButton : MainMenuButton
{
public:
	UpAndDownButton();
	UpAndDownButton(const UpAndDownButton& other);
	virtual ~UpAndDownButton();

	virtual bool InitializeEx(Direct2DEngine* D2DEngine, int x, int y, int width, int height, WCHAR* text);
	virtual bool Render();
	virtual bool Release();
};

