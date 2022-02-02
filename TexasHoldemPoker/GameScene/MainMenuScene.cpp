#include "MainMenuScene.h"
#include "SceneManager.h"

MainMenuScene::MainMenuScene()
{

}

MainMenuScene::MainMenuScene(const MainMenuScene& other)
{

}

MainMenuScene::~MainMenuScene()
{

}

bool MainMenuScene::Initialize(Direct2DEngine* d2dEngine, AudioEngine* audioEngine, GameOption* gameOption)
{
	GameScene::Initialize(d2dEngine, audioEngine, gameOption);
	WCHAR TitlePath[] = L"./Resource/Image/Title.png";
	m_Title.Initialize(extEngine, extGameOption->GetWidth() / 4,
		extGameOption->GetHeight() / 16,
		extGameOption->GetWidth() / 2,
		extGameOption->GetHeight() / 2,
		TitlePath);

	// Button
	m_SinglePlayButton = new MainMenuButton;
	if (m_SinglePlayButton->InitializeEx(extEngine, extGameOption->GetWidth() / 2 - ScalingUI_X(200, extGameOption->GetWidth()),
		ScalingUI_Y(550, extGameOption->GetHeight()),
		ScalingUI_X(400, extGameOption->GetWidth()),
		ScalingUI_Y(70, extGameOption->GetHeight()),
		const_cast<WCHAR*>(L"Single Play")))
	{
		m_SinglePlayButton->SetEvent(ButtonEvent::ButtonEvent_MainMenu_GoToSinglePlay);
	}

	m_MultiPlayButton = new MainMenuButton;
	if (m_MultiPlayButton->InitializeEx(extEngine, extGameOption->GetWidth() / 2 - ScalingUI_X(200, extGameOption->GetWidth()),
		ScalingUI_Y(670, extGameOption->GetHeight()),
		ScalingUI_X(400, extGameOption->GetWidth()),
		ScalingUI_Y(70, extGameOption->GetHeight()),
		const_cast<WCHAR*>(L"Multi Play")))
	{
		m_MultiPlayButton->SetEvent(ButtonEvent::ButtonEvent_MainMenu_GoToMultiPlay);
	}

	m_OptionButton = new MainMenuButton;
	if (m_OptionButton->InitializeEx(extEngine, extGameOption->GetWidth() / 2 - ScalingUI_X(200, extGameOption->GetWidth()),
		ScalingUI_Y(790, extGameOption->GetHeight()),
		ScalingUI_X(400, extGameOption->GetWidth()),
		ScalingUI_Y(70, extGameOption->GetHeight()),
		const_cast<WCHAR*>(L"Option")))
	{
		m_OptionButton->SetEvent(ButtonEvent::ButtonEvent_MainMenu_GoToOption);
	}

	m_ExitButton = new MainMenuButton;
	if (m_ExitButton->InitializeEx(extEngine, extGameOption->GetWidth() / 2 - ScalingUI_X(200, extGameOption->GetWidth()),
		ScalingUI_Y(910, extGameOption->GetHeight()),
		ScalingUI_X(400, extGameOption->GetWidth()),
		ScalingUI_Y(70, extGameOption->GetHeight()),
		const_cast<WCHAR*>(L"Exit")))
	{
		m_ExitButton->SetEvent(ButtonEvent::ButtonEvent_MainMenu_GoToExit);
	}

	return true;
}

bool MainMenuScene::Render()
{
	m_Title.Draw();
	m_SinglePlayButton->Render();
	m_MultiPlayButton->Render();
	m_OptionButton->Render();
	m_ExitButton->Render();
	return true;
}

bool MainMenuScene::Update()
{
	return true;
}

bool MainMenuScene::Release()
{
	SAFE_RELEASE_AND_DELETE(m_ExitButton);
	SAFE_RELEASE_AND_DELETE(m_OptionButton);
	SAFE_RELEASE_AND_DELETE(m_MultiPlayButton);
	SAFE_RELEASE_AND_DELETE(m_SinglePlayButton);

	m_Title.Release();
	return true;
}

LRESULT MainMenuScene::SceneProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);

	switch (message)
	{
	case WM_MOUSEMOVE:
		if (m_SinglePlayButton->IsInside(pt.x, pt.y))
		{
			m_SinglePlayButton->Touched();
		}
		else
			m_SinglePlayButton->Normally();

		if (m_MultiPlayButton->IsInside(pt.x, pt.y))
		{
			m_MultiPlayButton->Touched();
		}
		else
			m_MultiPlayButton->Normally();

		if (m_OptionButton->IsInside(pt.x, pt.y))
		{
			m_OptionButton->Touched();
		}
		else
			m_OptionButton->Normally();

		if (m_ExitButton->IsInside(pt.x, pt.y))
		{
			m_ExitButton->Touched();
		}
		else
			m_ExitButton->Normally();

		break;
	case WM_LBUTTONDOWN: // Mouse Click & Event
		if (m_SinglePlayButton->IsInside(pt.x, pt.y))
		{
			m_SinglePlayButton->Pressed();
			break;
		}

		if (m_MultiPlayButton->IsInside(pt.x, pt.y))
		{
			m_MultiPlayButton->Pressed();
			break;
		}

		if (m_OptionButton->IsInside(pt.x, pt.y))
		{
			m_OptionButton->Pressed();
			break;
		}

		if (m_ExitButton->IsInside(pt.x, pt.y))
		{
			m_ExitButton->Pressed();
			break;
		}

		break;
	case WM_LBUTTONUP:
		if (m_SinglePlayButton->IsInside(pt.x, pt.y))
		{
			m_SinglePlayButton->Touched();
			SceneManager::instance().EventListen(m_SinglePlayButton->GetEvent());
			break;
		}

		if (m_MultiPlayButton->IsInside(pt.x, pt.y))
		{
			m_MultiPlayButton->Touched();
			SceneManager::instance().EventListen(m_MultiPlayButton->GetEvent());
			break;
		}

		if (m_OptionButton->IsInside(pt.x, pt.y))
		{
			m_OptionButton->Touched();
			SceneManager::instance().EventListen(m_OptionButton->GetEvent());
			break;
		}

		if (m_ExitButton->IsInside(pt.x, pt.y))
		{
			m_ExitButton->Touched();
			SceneManager::instance().EventListen(m_ExitButton->GetEvent());
			break;
		}
	}
	return 0;
}