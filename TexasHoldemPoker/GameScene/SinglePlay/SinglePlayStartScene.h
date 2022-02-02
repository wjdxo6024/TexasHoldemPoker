#pragma once
#ifndef _SINGLEPLAYSTARTSCENE_H_
#define _SINGLEPLAYSTARTSCENE_H_
#include "../GameScene.h"

// SinglePlayStartScene ���� ���۽� �ִϸ��̼ǵ��� �����ִ� ��.
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