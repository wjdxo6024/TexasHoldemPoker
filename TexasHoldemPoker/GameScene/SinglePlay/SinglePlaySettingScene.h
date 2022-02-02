#pragma once
#ifndef _SINGLEPLAYSETTINGSCENE_H_
#define _SINGLEPLAYSETTINGSCENE_H_

#include "../GameScene.h"
#include "../../Direct2D/CustomUI/MainMenuButton.h"
#include "../../Direct2D/AdvancedUI/TextOutputField.h"
#include "../../Direct2D/CustomUI/CustomTextInputField.h"
#include "../../Direct2D/CustomUI/NumberInputField.h"
#include "../../Funtions/MyFunctions.h"

using namespace MyFunctions;
// 플레이어의 이름을 정하거나 게임 최대인원을 정하는 곳

class SinglePlaySettingScene : public GameScene
{
private:
	MainMenuButton* m_BackButton;
	MainMenuButton* m_StartButton;

	TextOutputField* m_TitleField;
	TextOutputField* m_NameField;
	TextOutputField* m_NumberField;

	CustomTextInputField* m_NameInputField;
	NumberInputField* m_NumberInputField;

	int m_PlayersNumber;
	std::wstring m_PlayerName;
public:
	SinglePlaySettingScene();
	SinglePlaySettingScene(const SinglePlaySettingScene& other);
	virtual ~SinglePlaySettingScene();

	bool Initialize(Direct2DEngine* d2dEngine, AudioEngine* audioEngine, GameOption* gameOption);
	bool Render();
	bool Update();
	bool Release();

	void SummitData(int& playersNumber, std::wstring& playerName);

	LRESULT SceneProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif