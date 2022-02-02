#pragma once
#ifndef _MAINMENU_H_
#define _MAINMENU_H_
#include "GameScene.h"
#include "../Direct2D/CustomUI/MainMenuButton.h"
#include "../Direct2D/BasicUI/CBitmap.h"
#include "../GameSound/Sound.h"
#include "../Funtions/MyFunctions.h"
using namespace MyFunctions;

class MainMenuScene : public GameScene
{
private:
	CBitmap m_Title;

	MainMenuButton* m_SinglePlayButton;
	MainMenuButton* m_MultiPlayButton;
	MainMenuButton* m_OptionButton;
	MainMenuButton* m_ExitButton;
public:
	MainMenuScene();
	MainMenuScene(const MainMenuScene& other);
	virtual ~MainMenuScene();

	bool Initialize(Direct2DEngine* d2dEngine, AudioEngine* audioEngine, GameOption* gameOption);
	bool Render();
	bool Update();
	bool Release();

	LRESULT SceneProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif
