#pragma once
#include "../Direct2D/BasicUI/CBitmap.h"
#include "GameScene.h"
#include "LoadingScene.h"
#include "MainMenuScene.h"
#include "OptionScene.h"
#include "SinglePlayScene.h"
#include "MultiPlayScene.h"
#include "ExitScene.h"

// ----------------------------------------------
// 싱글톤 패턴으로 구현
// ----------------------------------------------

enum Scenes
{
	Scene_Empty, // 비어있는 씬
	Scene_Loading,
	Scene_MainMenu,
	Scene_SinglePlay,
	// Multi --------------------
	Scene_MultiPlay,
	// --------------------------
	Scene_Option,
	Scene_Exit
};

enum SceneState
{
	SceneState_Idle, // 아무것도 안함
	SceneState_Ready,  // 초기화
	SceneState_Play, // 렌더 및 플레이
	SceneState_Quit // 릴리즈
};

class SceneManager
{
private:
	CBitmap* m_Background;
	Sound* MainBGM;

	Scenes m_CurrentScene;
	Scenes m_BeforeScene;

	SceneState m_SceneState;

	GameScene* m_CurrentGameScene;
	GameScene* m_LoadingScene;

	Direct2DEngine* extEngine;
	AudioEngine* extAudioEngine;
	GameOption* extGameOption;
private:
	SceneManager();
	SceneManager(const SceneManager& other);
	~SceneManager();

public:
	bool Initialize(Direct2DEngine* d2dEngine, AudioEngine* audioEngine, GameOption* gameOption);
	bool Render();
	bool Update();
	bool Release();

	bool ChangeScene(Scenes scene);
	bool EventListen(ButtonEvent _event);
	LRESULT SceneProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// -------------------------------
	static SceneManager& instance();

	Direct2DEngine* GetD2DEngine();
	AudioEngine* GetAudioEngine();
	GameOption* GetGameOption();
	void OnResize();
	Sound* GetMainBGM();
};

