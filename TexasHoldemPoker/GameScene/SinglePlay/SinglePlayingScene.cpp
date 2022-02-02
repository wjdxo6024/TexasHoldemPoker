#include "SinglePlayingScene.h"
#include "../SceneManager.h"


SinglePlayingScene::SinglePlayingScene()
{

}

SinglePlayingScene::SinglePlayingScene(const SinglePlayingScene& other)
{

}

SinglePlayingScene::~SinglePlayingScene()
{

}

bool SinglePlayingScene::Initialize(Direct2DEngine* D2DEngine, AudioEngine* audioEngine, GameOption* gameOption, std::wstring playerName, int numOfPlayers)
{
	GameScene::Initialize(D2DEngine, audioEngine, gameOption);
	m_PlayerName = playerName;
	m_NumberOfPlayers = numOfPlayers;

	m_GameTime.Initialize();

	// Player Init
	for (int i = 0; i < m_NumberOfPlayers; i++)
	{
		Player player;
		if (i == 0) // 플레이어 초기화
		{
			InitPlayer(&player, m_PlayerName.c_str(), false);
			m_Players.push_back(player);
		}
		else // AI 초기화
		{
			InitPlayer(&player, L"", true);
		}
	}


	// --------------------------------------------------------
	

	m_CardImages = new CardImages;
	if (m_CardImages != NULL)
	{
		m_CardImages->Initialize(extEngine, extGameOption, const_cast<WCHAR*>(L"./Resource/Image/CardImage.png"));
	}
	else
		return false;

	// UI Setting ---------------------------------------------
	m_BackButton = new MainMenuButton;
	if (m_BackButton != NULL)
	{
		m_BackButton->InitializeEx(extEngine, 10,
			10,
			ScalingUI_Y(70, gameOption->GetHeight()),
			ScalingUI_Y(70, gameOption->GetHeight()),
			const_cast<WCHAR*>(L"◀"));

		m_BackButton->SetEvent(ButtonEvent::ButtonEvent_SinglePlay_Back);
	}
	else
		return false;

	m_PokerUI = new PokerUI;
	if (m_PokerUI != NULL)
	{
		m_PokerUI->Initialize(extEngine, extGameOption, m_CardImages);
	}
	else
		return false;

	// --------------------------------------------------------

	m_StartAnimation = new StartAnimation;
	if (m_StartAnimation != NULL)
	{
		m_StartAnimation->Initialize(extEngine, extGameOption, extAudioEngine);
		m_StartAnimation->SetText(L"START");
	}
	else
		return false;

	PlayBGM = new BackGroundSound();
	if (PlayBGM != NULL)
	{
		PlayBGM->InitializeBasic(L"./Resource/Audio/PlayBGM.wav", extAudioEngine, gameOption);
	}
	PlayBGM->Play();
	return true;
}

bool SinglePlayingScene::Render()
{
	m_CardImages->Draw(100, 100);
	m_PokerUI->Render();


	m_StartAnimation->Render();
	return true;
}

bool SinglePlayingScene::Update()
{
	m_GameTime.Update();
	m_StartAnimation->Update(m_GameTime.GetDeltaTime());
	return true;
}

bool SinglePlayingScene::Release()
{
	PlayBGM->Stop();
	SAFE_RELEASE_AND_DELETE(PlayBGM);
	SAFE_RELEASE_AND_DELETE(m_StartAnimation);
	SAFE_RELEASE_AND_DELETE(m_PokerUI);
	SAFE_RELEASE_AND_DELETE(m_BackButton);
	SAFE_RELEASE_AND_DELETE(m_CardImages);
	return true;
}

bool SinglePlayingScene::Start()
{
	m_StartAnimation->Start();
	reinterpret_cast<BackGroundSound*>(SceneManager::instance().GetMainBGM())->Stop();
	return true;
}

bool SinglePlayingScene::End()
{
	return true;
}

LRESULT SinglePlayingScene::SceneProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (Is_Animate)
	{
		switch (message)
		{
			
		}
	}
	else
	{
		switch (message)
		{

		}
	}

	return 0;
}

