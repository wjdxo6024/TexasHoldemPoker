#pragma once
#include "MainMenuButton.h"
class BackButton :
	public MainMenuButton
{
public:
	BackButton();
	BackButton(const BackButton& other);
	virtual ~BackButton();

	virtual bool InitializeEx(Direct2DEngine* D2DEngine, int x, int y, int width, int height, WCHAR* text);
	virtual bool Render();
	virtual bool Release();
};

