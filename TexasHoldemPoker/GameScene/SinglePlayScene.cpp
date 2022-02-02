#include "SinglePlayScene.h"

SinglePlayScene::SinglePlayScene()
{
	m_PlayingScene = NULL;
	m_SettingScene = NULL;
}

SinglePlayScene::SinglePlayScene(const SinglePlayScene& other)
{

}

SinglePlayScene::~SinglePlayScene()
{

}

bool SinglePlayScene::Initialize(Direct2DEngine* d2dEngine, AudioEngine* audioEngine, GameOption* gameOption)
{
	GameScene::Initialize(d2dEngine, audioEngine, gameOption);

	m_CurrentSceneState = SinglePlay_Setting;

	m_SettingScene = new SinglePlaySettingScene;
	if (m_SettingScene != NULL)
	{
		if (!m_SettingScene->Initialize(d2dEngine, audioEngine, gameOption))
		{
			return false;
		}
	}
	else
		return false;

	return true;
}

bool SinglePlayScene::Render()
{
	switch (m_CurrentSceneState)
	{
	case SinglePlay_Setting:
		m_SettingScene->Render();
		break;
	case SinglePlay_Start:
		// ½ºÅ¸Æ® ¾Ö´Ï¸ÞÀÌ¼Ç ¹× ÇÃ·¹À× ¾À
		break;
	case SinglePlay_End:
		// ÇÃ·¹À× ¾À À§¿¡ ¿£µå ¾À
		break;
	case SinglePlay_Playing:
		// ÇÃ·¹À× ¾À
		m_PlayingScene->Render();
		break;

	}
	return true;
}

bool SinglePlayScene::Update()
{
	switch (m_CurrentSceneState)
	{
	case SinglePlay_Setting:
		m_SettingScene->Update();
		break;
	case SinglePlay_Start:
		// ½ºÅ¸Æ® ¾Ö´Ï¸ÞÀÌ¼Ç ¹× ÇÃ·¹À× ¾À
		break;
	case SinglePlay_End:
		// ÇÃ·¹À× ¾À À§¿¡ ¿£µå ¾À
		break;
	case SinglePlay_Playing:
		// ÇÃ·¹À× ¾À
		m_PlayingScene->Update();
		break;

	}
	return true;
}

bool SinglePlayScene::Release()
{
	SAFE_RELEASE_AND_DELETE(m_PlayingScene);
	SAFE_RELEASE_AND_DELETE(m_SettingScene);
	return true;
}

void SinglePlayScene::ChangeScene(SinglePlayScenes scenes)
{
	m_CurrentSceneState = scenes;
	switch (m_CurrentSceneState)
	{
		case SinglePlay_Setting:
		{
			SAFE_RELEASE_AND_DELETE(m_PlayingScene);
			m_SettingScene = new SinglePlaySettingScene;
			m_SettingScene->Initialize(extEngine, extAudioEngine, extGameOption);
			break;
		}
		case SinglePlay_Start:
		{
			if (m_PlayingScene == NULL)
			{
				std::wstring PlayerName;
				int numOfPlayers;

				m_SettingScene->SummitData(numOfPlayers, PlayerName);

				m_PlayingScene = new SinglePlayingScene;
				m_PlayingScene->Initialize(extEngine, extAudioEngine, extGameOption, PlayerName, numOfPlayers);
			}

			SAFE_RELEASE_AND_DELETE(m_SettingScene);

			// Start Animation
			m_PlayingScene->Start();
			// -------------------------
			m_CurrentSceneState = SinglePlay_Playing;
			break;
		}
		case SinglePlay_Playing:
		{
			break;
		}
		case SinglePlay_End:
		{
			// End Animation
			break;
		}
	}
}

LRESULT SinglePlayScene::SceneProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (m_CurrentSceneState)
	{
	case SinglePlay_Setting:
		if (m_SettingScene->SceneProc(hWnd, message, wParam, lParam))
			ChangeScene(SinglePlay_Start);
		break;

	case SinglePlay_Start:
		// m_PlayingScene Start Animation;
		break;
	case SinglePlay_Playing:
		if (m_PlayingScene->SceneProc(hWnd, message, wParam, lParam))
			ChangeScene(SinglePlay_Setting);
		break;
	case SinglePlay_End:
		break;
	}
	return 0;
}