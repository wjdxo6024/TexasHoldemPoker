#include "GameScene.h"

GameScene::GameScene()
{

}

GameScene::GameScene(const GameScene& other)
{

}

GameScene::~GameScene()
{

}

bool GameScene::Initialize(Direct2DEngine* d2dEngine, AudioEngine* audioEngine, GameOption* gameOption)
{
	extEngine = d2dEngine;
	extAudioEngine = audioEngine;
	extGameOption = gameOption;
	return true;
}

bool GameScene::Render()
{
	return true;
}

bool GameScene::Update()
{
	return true;
}

bool GameScene::Release()
{
	return true;
}

LRESULT GameScene::SceneProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return 0;
}