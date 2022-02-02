#pragma once
#include "GameScene.h"
#include "../GameOption/GameOption.h"
#include "../Direct2D/Direct2DEngine.h"
#include "../Direct2D/CustomUI/MainMenuButton.h"
#include "../Direct2D/BasicUI/Text.h"
#include "../Direct2D/AdvancedUI/CheckBox.h"
#include "../Direct2D/CustomUI/CustomTextOutputField.h"
#include "../GameOption/SupportWindow.h"
using namespace MyFunctions;

class OptionScene : public GameScene
{
private:
	float m_BGMVolume;
	float m_EffectVolume;

	SupportWindow m_SupportWindow;
	bool m_CheckFullScreen;
	bool IsChange;

	CustomTextOutputField* m_ScreenTitleText;
	CustomTextOutputField* m_ScreenText;

	CustomTextOutputField* m_BGMTitleText;
	CustomTextOutputField* m_BGMText;

	CustomTextOutputField* m_EffectTitleText;
	CustomTextOutputField* m_EffectText;
	CustomTextOutputField* m_FullScreenText;

	MainMenuButton* m_BackButton;
	MainMenuButton* m_NextScreenButton;
	MainMenuButton* m_PrevScreenButton;
	MainMenuButton* m_BGMVolumeUpButton;
	MainMenuButton* m_BGMVolumeDownButton;
	MainMenuButton* m_EffectVolumeUpButton;
	MainMenuButton* m_EffectVolumeDownButton;
	MainMenuButton* m_SettingButton;
	CheckBox* m_FullScreenCheckBox;

public:
	OptionScene();
	OptionScene(const OptionScene& other);
	~OptionScene();

	bool Initialize(Direct2DEngine* d2dEngine, AudioEngine* audioEngine, GameOption* gameOption);
	bool Render();
	bool Update();
	bool Release();

	void OptionChange(HWND hWnd);

	LRESULT SceneProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

