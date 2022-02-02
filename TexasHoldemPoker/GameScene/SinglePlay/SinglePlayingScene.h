#pragma once
#ifndef _SINGLEPLAYINGSCENE_H_
#define _SINGLEPLAYINGSCENE_H_

extern "C"
{
#include "../../PokerRule/GameAI.h"
#include "../../PokerRule/PokerDefine.h"
#include "../../PokerRule/PokerRule.h"
}

#include <vector>
#include "../GameScene.h"
#include "../../Direct2D/AdvancedUI/Dialog.h"
#include "../../Direct2D/CustomUI/MainMenuButton.h"
#include "../../Direct2D/CustomUI/CardImages.h"
#include "../../Direct2D/CustomUI/PokerUI.h"
#include "../../GameUtility/GameTime.h"
#include "../../Direct2D/Animation/StartAnimation.h"
#include "../../Direct2D/CustomUI/CustomTextOutputField.h"
#include "../../GameSound/BackGroundSound.h"
// 실질적으로 게임이 이루어지는 씬.

class SinglePlayingScene : public GameScene
{
private:
	Sound* PlayBGM;
	EffectSound* ManFold;
	EffectSound* ManCall;
	EffectSound* ManRaise;
	EffectSound* WomanFold;
	EffectSound* WomanCall;
	EffectSound* WomanRaise;

	// Game System
	GameTime m_GameTime;
	int m_CurrentActionPlayer;
	bool Is_Animate; // 애니메이션 시 백 버튼을 제외한 나머지 요소 중지.

	// Poker Data
	int m_NumberOfPlayers;
	std::wstring m_PlayerName;
	std::vector<Player> m_Players;

	CardImages* m_CardImages;
	PokerUI* m_PokerUI;

	// Start Cut Scene
	StartAnimation* m_StartAnimation;
	// End Cut Scene

	// Back Button & Cut Scene
	MainMenuButton* m_BackButton;
	Dialog* m_YesNoDialog;
public:
	SinglePlayingScene();
	SinglePlayingScene(const SinglePlayingScene& other);
	virtual ~SinglePlayingScene();

	bool Initialize(Direct2DEngine* D2DEngine, AudioEngine* audioEngine, GameOption* gameOption, std::wstring playerName, int numOfPlayers);
	bool Render();
	bool Update();
	bool Release();

	bool Start(); // First Game Start
	bool Result(); // Game Result;
	bool End(); // Game End

	LRESULT SceneProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif