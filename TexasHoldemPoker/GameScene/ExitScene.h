#pragma once
#ifndef _EXITSCENE_H_
#define _EXITSCENE_H_
#include "GameScene.h"
#include "SceneManager.h"
#include "../Direct2D/CustomUI/MainMenuButton.h"
#include "../Direct2D/CustomUI/CustomTextOutputField.h"
#include "../Direct2D/BasicUI/CRectangle.h"
#include "../Funtions/MyFunctions.h"

using namespace MyFunctions;

class ExitScene :
	public GameScene
{
private:
	CRectangle* m_FadeOutRect;
	MainMenuButton* m_BackButton;
	MainMenuButton* m_YesButton;
	MainMenuButton* m_NoButton;
	CustomTextOutputField* m_ExitGuideText;

public:
	ExitScene();
	ExitScene(const ExitScene& other);
	virtual ~ExitScene();

	bool Initialize(Direct2DEngine* d2dEngine, AudioEngine* audioEngine, GameOption* gameOption);
	bool Render();
	bool Update();
	bool Release();

	LRESULT SceneProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif