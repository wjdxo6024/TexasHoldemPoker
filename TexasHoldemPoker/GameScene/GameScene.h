#pragma once
#include <Windows.h>
#include "../Direct3D/DirectXEngine.h"
#include "../Direct2D/Direct2DEngine.h"
#include "../GameSound/AudioEngine.h"
#include "../GameSound/BackGroundSound.h"
#include "../GameSound/EffectSound.h"

class GameScene
{
protected:
	GameOption* extGameOption;
	Direct2DEngine* extEngine;
	AudioEngine* extAudioEngine;

public:
	GameScene();
	GameScene(const GameScene& other);
	virtual ~GameScene();

	virtual bool Initialize(Direct2DEngine* d2dEngine, AudioEngine* audioEngine, GameOption* gameOption);
	virtual bool Render();
	virtual bool Update();
	virtual bool Release();

	virtual LRESULT SceneProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};