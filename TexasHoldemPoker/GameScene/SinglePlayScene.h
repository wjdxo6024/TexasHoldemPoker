#pragma once
#ifndef _SINGLEPLAYSCENE_H_
#define _SINGLEPLAYSCENE_H_

#include "PlaySceneDefine.h"
#include "SinglePlay/SinglePlaySettingScene.h"
#include "SinglePlay/SinglePlayingScene.h"

enum SinglePlayScenes
{
	SinglePlay_Setting,
	SinglePlay_Start,
	SinglePlay_Playing,
	SinglePlay_End
};

// class SinglePlaySettingScene;

class SinglePlayScene : public GameScene
{
private:
	SinglePlayScenes m_CurrentSceneState;
	SinglePlaySettingScene* m_SettingScene;
	SinglePlayingScene* m_PlayingScene;

public:
	SinglePlayScene();
	SinglePlayScene(const SinglePlayScene& other);
	virtual ~SinglePlayScene();

	bool Initialize(Direct2DEngine* d2dEngine, AudioEngine* audioEngine, GameOption* gameOption);
	bool Render();
	bool Update();
	bool Release();
	void ChangeScene(SinglePlayScenes scenes);

	LRESULT SceneProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif