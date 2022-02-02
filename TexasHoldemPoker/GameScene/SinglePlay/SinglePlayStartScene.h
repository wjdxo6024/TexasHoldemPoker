#pragma once
#ifndef _SINGLEPLAYSTARTSCENE_H_
#define _SINGLEPLAYSTARTSCENE_H_
#include "../GameScene.h"

// SinglePlayStartScene 게임 시작시 애니메이션등을 보여주는 씬.
class SinglePlayStartScene : public GameScene
{
private:

public:
	bool Initialize();
	bool Update();
	bool Render();
	bool Release();


	LRESULT SceneProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif