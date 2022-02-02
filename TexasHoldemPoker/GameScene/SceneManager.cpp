#include "SceneManager.h"

SceneManager::SceneManager()
{
	m_CurrentScene = Scene_Empty;
	m_CurrentGameScene = NULL;
	m_LoadingScene = NULL;
	m_SceneState = SceneState_Idle;

}

SceneManager::SceneManager(const SceneManager& other)
{

}

SceneManager::~SceneManager()
{
	this->Release();
}

bool SceneManager::Initialize(Direct2DEngine* d2dEngine, AudioEngine* audioEngine, GameOption* gameOption)
{
	extEngine = d2dEngine;
	extAudioEngine = audioEngine;
	extGameOption = gameOption;
	m_SceneState = SceneState_Idle;
	m_CurrentScene = Scene_MainMenu;

	MainBGM = new BackGroundSound();
	if (MainBGM != NULL)
	{
		MainBGM->InitializeBasic(L"./Resource/Audio/MainBGM.wav", extAudioEngine, gameOption);
	}


	m_Background = new CBitmap();
	m_Background->Initialize(extEngine, 0, 0, extGameOption->GetWidth(), extGameOption->GetHeight(), const_cast<WCHAR*>(L"./Resource/Image/PokerTable.jpg"));

	m_CurrentGameScene = new MainMenuScene();
	if (m_CurrentGameScene != NULL)
	{
		m_CurrentGameScene->Initialize(extEngine, extAudioEngine, extGameOption);
	}

	MainBGM->Play();
	m_SceneState = SceneState_Ready;
	return true;
}

bool SceneManager::Render()
{

	m_Background->Draw();

	if (m_SceneState == SceneState_Ready)
		m_SceneState = SceneState_Play;

	m_CurrentGameScene->Render();
	return true;
}

bool SceneManager::Update()
{
	return m_CurrentGameScene->Update();
}

bool SceneManager::Release()
{
	if (m_CurrentGameScene != NULL)
	{
		m_CurrentGameScene->Release();
		delete m_CurrentGameScene;
		m_CurrentGameScene = 0;
	}

	if (m_LoadingScene != NULL)
	{
		m_LoadingScene->Release();
		delete m_CurrentGameScene;
		m_LoadingScene = 0;
	}

	MainBGM->Stop();
	SAFE_RELEASE_AND_DELETE(m_Background);
	SAFE_RELEASE_AND_DELETE(MainBGM);
	m_SceneState = SceneState_Quit;
	return true;
}

bool SceneManager::ChangeScene(Scenes scene)
{
	if (scene == m_CurrentScene)
		return true;

	if (m_CurrentGameScene != NULL)
	{
		m_CurrentGameScene->Release();
		delete m_CurrentGameScene;
	}

	m_SceneState = SceneState_Idle;
	m_CurrentScene = scene;
	switch (scene)
	{
	case Scenes::Scene_MainMenu:
	{
		MainBGM->Play();
		m_CurrentGameScene = new MainMenuScene;
		if (m_CurrentGameScene != NULL)
		{
			m_CurrentGameScene->Initialize(extEngine, extAudioEngine, extGameOption);
		}
		break;
	}
	case Scenes::Scene_SinglePlay:
	{
		m_CurrentGameScene = new SinglePlayScene;
		if (m_CurrentGameScene != NULL)
		{
			m_CurrentGameScene->Initialize(extEngine, extAudioEngine, extGameOption);
		}
		break;
	}
	case Scenes::Scene_MultiPlay:
	{
		m_CurrentGameScene = new MultiPlayScene;
		if (m_CurrentGameScene != NULL)
		{
			m_CurrentGameScene->Initialize(extEngine, extAudioEngine, extGameOption);
		}
		break;
	}

	case Scenes::Scene_Option:
	{
		m_CurrentGameScene = new OptionScene;
		if (m_CurrentGameScene != NULL)
		{
			m_CurrentGameScene->Initialize(extEngine, extAudioEngine, extGameOption);
		}
		break;
	}
	case Scenes::Scene_Exit:
	{
		m_CurrentGameScene = new ExitScene;
		if (m_CurrentGameScene != NULL)
		{
			m_CurrentGameScene->Initialize(extEngine, extAudioEngine, extGameOption);
		}
		break;
	}
	default:
		break;
	}
	m_SceneState = SceneState_Ready;
	return true;
}

bool SceneManager::EventListen(ButtonEvent _event)
{
	switch (_event)
	{
	case ButtonEvent::ButtonEvent_MainMenu_GoToSinglePlay:
		this->ChangeScene(Scene_SinglePlay);
		break;
	case ButtonEvent::ButtonEvent_MainMenu_GoToMultiPlay:
		this->ChangeScene(Scene_MultiPlay);
		break;
	case ButtonEvent::ButtonEvent_MainMenu_GoToOption:
		this->ChangeScene(Scene_Option);
		break;
	case ButtonEvent::ButtonEvent_MainMenu_GoToExit:
		this->ChangeScene(Scene_Exit);
		break;
	case ButtonEvent::ButtonEvent_SinglePlay_Back:
	case ButtonEvent::ButtonEvent_MultiPlay_Back:
	case ButtonEvent::ButtonEvent_Option_Back:
		this->ChangeScene(Scene_MainMenu);
		break;

	case ButtonEvent::ButtonEvent_Option_BackGroundSoundVolumeDown:
	case ButtonEvent::ButtonEvent_Option_BackGroundSoundVolumeUp:
		if (MainBGM != NULL)
		{
			MainBGM->Update();
		}
		break;

	case ButtonEvent::ButtonEvent_Exit_Back:
	case ButtonEvent::ButtonEvent_Exit_No:
		this->ChangeScene(Scene_MainMenu);
		break;
	case ButtonEvent::ButtonEvent_Exit_Yes:
		PostQuitMessage(0);
		break;
	}

	return true;
}

LRESULT SceneManager::SceneProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if(m_SceneState == SceneState_Play)
		m_CurrentGameScene->SceneProc(hWnd, message, wParam, lParam);
	// SceneManager Proc
	switch (message)
	{
	case WM_KEYDOWN:
	{
		break;
	}
	case WM_MOUSEMOVE:
		break;
	}
	return 0;
}

SceneManager& SceneManager::instance()
{
	static SceneManager instance_;
	return instance_;
}

Direct2DEngine* SceneManager::GetD2DEngine()
{
	return extEngine;
}

AudioEngine* SceneManager::GetAudioEngine()
{
	return extAudioEngine;
}

GameOption* SceneManager::GetGameOption()
{
	return extGameOption;
}

void SceneManager::OnResize()
{
	// Direct2D와 Direct3D에 관련된 모든 요소들을 Release, Initialize한다.
	m_Background->Release();
	m_Background->Initialize(extEngine, 0, 0, extGameOption->GetWidth(), extGameOption->GetHeight(), const_cast<WCHAR*>(L"./Resource/Image/PokerTable.jpg"));
}

Sound* SceneManager::GetMainBGM()
{
	return MainBGM;
}