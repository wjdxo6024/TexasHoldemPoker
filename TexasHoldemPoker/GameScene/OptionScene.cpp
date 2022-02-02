#include "OptionScene.h"
#include "SceneManager.h"
OptionScene::OptionScene()
{
	m_BackButton = NULL;
	m_BGMVolumeDownButton = NULL;
	m_BGMVolumeUpButton = NULL;
	m_EffectVolumeDownButton = NULL;
	m_EffectVolumeUpButton = NULL;
	m_FullScreenCheckBox = NULL;
	m_NextScreenButton = NULL;
	m_PrevScreenButton = NULL;
	m_SettingButton = NULL;
	m_FullScreenCheckBox = NULL;

	m_BGMText = NULL;
	m_EffectText = NULL;
	m_FullScreenText = NULL;
	m_ScreenText = NULL;

	// Temp Initialize
	m_BGMVolume = 1.0f;
	m_EffectVolume = 1.0f;
	m_CheckFullScreen = false;
}

OptionScene::OptionScene(const OptionScene& other)
{

}

OptionScene::~OptionScene()
{

}

bool OptionScene::Initialize(Direct2DEngine* d2dEngine, AudioEngine* audioEngine, GameOption* gameOption)
{
	GameScene::Initialize(d2dEngine, audioEngine, gameOption);

	m_BGMVolume = extAudioEngine->GetBackGroundVolume();
	m_EffectVolume = extAudioEngine->GetEffectVolume();
	m_SupportWindow = SupportWindow(extGameOption->GetWidth(), extGameOption->GetHeight());
	m_CheckFullScreen = extGameOption->GetFullScreen();

	IsChange = false;

	m_BackButton = new MainMenuButton;
	if (m_BackButton != NULL)
	{
		m_BackButton->InitializeEx(extEngine, 10,
			10,
			ScalingUI_Y(70, gameOption->GetHeight()),
			ScalingUI_Y(70, gameOption->GetHeight()),
			const_cast<WCHAR*>(L"◀"));

		m_BackButton->SetEvent(ButtonEvent::ButtonEvent_Option_Back);
	}
	else
		return false;

	m_NextScreenButton = new MainMenuButton;
	if (m_NextScreenButton != NULL)
	{
		m_NextScreenButton->InitializeEx(extEngine, extGameOption->GetWidth() / 2 + ScalingUI_X(300, extGameOption->GetWidth()),
			ScalingUI_Y(150, extGameOption->GetHeight()),
			ScalingUI_Y(100, extGameOption->GetHeight()),
			ScalingUI_Y(100, extGameOption->GetHeight()),
			const_cast<WCHAR*>(L"▶"));

		m_NextScreenButton->SetEvent(ButtonEvent::ButtonEvent_Option_WindowSizeUp);
		m_NextScreenButton->GetText()->SetFontSize(m_NextScreenButton->GetText()->GetFontSize() * 2);
	}
	else
		return false;

	m_PrevScreenButton = new MainMenuButton;
	if (m_PrevScreenButton != NULL)
	{
		m_PrevScreenButton->InitializeEx(extEngine, extGameOption->GetWidth() / 2 - ScalingUI_X(400, extGameOption->GetWidth()),
			ScalingUI_Y(150, extGameOption->GetHeight()),
			ScalingUI_Y(100, extGameOption->GetHeight()),
			ScalingUI_Y(100, extGameOption->GetHeight()),
			const_cast<WCHAR*>(L"◀"));

		m_PrevScreenButton->SetEvent(ButtonEvent::ButtonEvent_Option_WindowSizeDown);
		m_PrevScreenButton->GetText()->SetFontSize(m_PrevScreenButton->GetText()->GetFontSize() * 2);
	}
	else
		return false;

	m_BGMVolumeUpButton = new MainMenuButton;
	if (m_BGMVolumeUpButton != NULL)
	{
		m_BGMVolumeUpButton->InitializeEx(extEngine, extGameOption->GetWidth() / 2 + ScalingUI_X(300, extGameOption->GetWidth()),
			ScalingUI_Y(350, extGameOption->GetHeight()),
			ScalingUI_Y(100, extGameOption->GetHeight()),
			ScalingUI_Y(100, extGameOption->GetHeight()),
			const_cast<WCHAR*>(L"▶"));

		m_BGMVolumeUpButton->SetEvent(ButtonEvent::ButtonEvent_Option_BackGroundSoundVolumeUp);
		m_BGMVolumeUpButton->GetText()->SetFontSize(m_BGMVolumeUpButton->GetText()->GetFontSize() * 2);
	}
	else
		return false;

	m_BGMVolumeDownButton = new MainMenuButton;
	if (m_BGMVolumeDownButton != NULL)
	{
		m_BGMVolumeDownButton->InitializeEx(extEngine, extGameOption->GetWidth() / 2 - ScalingUI_X(400, extGameOption->GetWidth()),
			ScalingUI_Y(350, extGameOption->GetHeight()),
			ScalingUI_Y(100, extGameOption->GetHeight()),
			ScalingUI_Y(100, extGameOption->GetHeight()),
			const_cast<WCHAR*>(L"◀"));

		m_BGMVolumeDownButton->SetEvent(ButtonEvent::ButtonEvent_Option_BackGroundSoundVolumeDown);
		m_BGMVolumeDownButton->GetText()->SetFontSize(m_BGMVolumeDownButton->GetText()->GetFontSize() * 2);
	}
	else
		return false;

	m_EffectVolumeUpButton = new MainMenuButton;
	if (m_EffectVolumeUpButton != NULL)
	{
		m_EffectVolumeUpButton->InitializeEx(extEngine, extGameOption->GetWidth() / 2 + ScalingUI_X(300, extGameOption->GetWidth()),
			ScalingUI_Y(550, extGameOption->GetHeight()),
			ScalingUI_Y(100, extGameOption->GetHeight()),
			ScalingUI_Y(100, extGameOption->GetHeight()),
			const_cast<WCHAR*>(L"▶"));

		m_EffectVolumeUpButton->SetEvent(ButtonEvent::ButtonEvent_Option_EffectSoundVolumeUp);
		m_EffectVolumeUpButton->GetText()->SetFontSize(m_EffectVolumeUpButton->GetText()->GetFontSize() * 2);
	}
	else
		return false;

	m_EffectVolumeDownButton = new MainMenuButton;
	if (m_EffectVolumeDownButton != NULL)
	{
		m_EffectVolumeDownButton->InitializeEx(extEngine, extGameOption->GetWidth() / 2 - ScalingUI_X(400, extGameOption->GetWidth()),
			ScalingUI_Y(550, extGameOption->GetHeight()),
			ScalingUI_Y(100, extGameOption->GetHeight()),
			ScalingUI_Y(100, extGameOption->GetHeight()),
			const_cast<WCHAR*>(L"◀"));

		m_EffectVolumeDownButton->SetEvent(ButtonEvent::ButtonEvent_Option_EffectSoundVolumeDown);
		m_EffectVolumeDownButton->GetText()->SetFontSize(m_EffectVolumeDownButton->GetText()->GetFontSize() * 2);
	}
	else
		return false;

	m_SettingButton = new MainMenuButton;
	if (m_SettingButton != NULL)
	{
		m_SettingButton->InitializeEx(extEngine, (extGameOption->GetWidth() / 2) - ScalingUI_X(100, extGameOption->GetWidth()),
			ScalingUI_Y(900, extGameOption->GetHeight()),
			ScalingUI_Y(200, extGameOption->GetHeight()),
			ScalingUI_Y(100, extGameOption->GetHeight()),
			const_cast<WCHAR*>(L"Apply"));

		m_SettingButton->SetEvent(ButtonEvent::ButtonEvent_Confirm);
	}
	else
		return false;
	
	m_FullScreenCheckBox = new CheckBox;
	if (m_FullScreenCheckBox != NULL)
	{
		m_FullScreenCheckBox->Initialize(extEngine, extGameOption->GetWidth() / 2 + ScalingUI_X(300, extGameOption->GetWidth()),
			ScalingUI_Y(750, extGameOption->GetHeight()),
			ScalingUI_Y(100, extGameOption->GetHeight()),
			ScalingUI_Y(100, extGameOption->GetHeight()));

		m_FullScreenCheckBox->SetCheck(m_CheckFullScreen);
	}
	else
		return false;

	// -300 -200 | 300
	m_ScreenText = new CustomTextOutputField;
	if (m_ScreenText != NULL)
	{
		m_ScreenText->Initialize(extEngine, extGameOption->GetWidth() / 2 - ScalingUI_X(250, extGameOption->GetWidth()),
			ScalingUI_Y(150, extGameOption->GetHeight()),
			ScalingUI_X(500, extGameOption->GetWidth()),
			ScalingUI_Y(100, extGameOption->GetHeight()));
		
		m_ScreenText->GetText()->SetTextWidthAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
		m_ScreenText->GetText()->SetTextHeightAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		m_ScreenText->GetText()->SetFontSize(m_ScreenText->GetText()->GetFontSize() * 2);
		m_ScreenText->SetTextContent(const_cast<WCHAR*>(L"Screen Text"));
		/*m_ScreenText->CreateRectangle();*/
	}

	m_BGMText = new CustomTextOutputField;
	if (m_BGMText != NULL)
	{
		m_BGMText->Initialize(extEngine, extGameOption->GetWidth() / 2 - ScalingUI_X(250, extGameOption->GetWidth()),
			ScalingUI_Y(350, extGameOption->GetHeight()),
			ScalingUI_X(500, extGameOption->GetWidth()),
			ScalingUI_Y(100, extGameOption->GetHeight()));

		m_BGMText->GetText()->SetTextWidthAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
		m_BGMText->GetText()->SetTextHeightAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		m_BGMText->GetText()->SetFontSize(m_BGMText->GetText()->GetFontSize() * 2);
		m_BGMText->SetTextContent(const_cast<WCHAR*>(L"BGM Text"));
		//m_BGMText->CreateRectangle();
	}

	m_EffectText = new CustomTextOutputField;
	if (m_EffectText != NULL)
	{
		m_EffectText->Initialize(extEngine, extGameOption->GetWidth() / 2 - ScalingUI_X(250, extGameOption->GetWidth()),
			ScalingUI_Y(550, extGameOption->GetHeight()),
			ScalingUI_X(500, extGameOption->GetWidth()),
			ScalingUI_Y(100, extGameOption->GetHeight()));

		m_EffectText->GetText()->SetTextWidthAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
		m_EffectText->GetText()->SetTextHeightAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		m_EffectText->GetText()->SetFontSize(m_EffectText->GetText()->GetFontSize() * 2);
		m_EffectText->SetTextContent(const_cast<WCHAR*>(L"Effect Text"));
		//m_EffectText->CreateRectangle();
	}

	m_FullScreenText = new CustomTextOutputField;
	if (m_FullScreenText != NULL)
	{
		m_FullScreenText->Initialize(extEngine, extGameOption->GetWidth() / 2 - ScalingUI_X(250, extGameOption->GetWidth()),
			ScalingUI_Y(750, extGameOption->GetHeight()),
			ScalingUI_X(500, extGameOption->GetWidth()),
			ScalingUI_Y(100, extGameOption->GetHeight()));

		m_FullScreenText->GetText()->SetTextWidthAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
		m_FullScreenText->GetText()->SetTextHeightAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		m_FullScreenText->GetText()->SetFontSize(m_FullScreenText->GetText()->GetFontSize() * 2);
		m_FullScreenText->SetTextContent(const_cast<WCHAR*>(L"Full Screen"));
	}

	m_ScreenTitleText = new CustomTextOutputField;
	if (m_ScreenTitleText != NULL)
	{
		m_ScreenTitleText->Initialize(extEngine, extGameOption->GetWidth() / 2 - ScalingUI_X(800, extGameOption->GetWidth()),
			ScalingUI_Y(150, extGameOption->GetHeight()),
			ScalingUI_X(300, extGameOption->GetHeight()),
			ScalingUI_Y(100, extGameOption->GetHeight()));

		m_ScreenTitleText->GetText()->SetTextHeightAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		m_ScreenTitleText->GetText()->SetFontSize(m_ScreenTitleText->GetText()->GetFontSize() * 1.5);
		m_ScreenTitleText->SetTextContent(const_cast<WCHAR*>(L"Screen Size "));
		//m_ScreenTitleText->CreateRectangle();
	}

	m_BGMTitleText = new CustomTextOutputField;
	if (m_BGMTitleText != NULL)
	{
		m_BGMTitleText->Initialize(extEngine, extGameOption->GetWidth() / 2 - ScalingUI_X(800, extGameOption->GetWidth()),
			ScalingUI_Y(350, extGameOption->GetHeight()),
			ScalingUI_X(300, extGameOption->GetWidth()),
			ScalingUI_Y(100, extGameOption->GetHeight()));

		m_BGMTitleText->GetText()->SetTextHeightAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		m_BGMTitleText->GetText()->SetFontSize(m_BGMTitleText->GetText()->GetFontSize() * 1.5);
		m_BGMTitleText->SetTextContent(const_cast<WCHAR*>(L"BGM Volume "));
		//m_BGMTitleText->CreateRectangle();
	}

	m_EffectTitleText = new CustomTextOutputField;
	if (m_EffectTitleText != NULL)
	{
		m_EffectTitleText->Initialize(extEngine, extGameOption->GetWidth() / 2 - ScalingUI_X(800, extGameOption->GetWidth()),
			ScalingUI_Y(550, extGameOption->GetHeight()),
			ScalingUI_X(300, extGameOption->GetWidth()),
			ScalingUI_Y(100, extGameOption->GetHeight()));

		m_EffectTitleText->GetText()->SetTextHeightAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		m_EffectTitleText->GetText()->SetFontSize(m_EffectTitleText->GetText()->GetFontSize() * 1.5);
		m_EffectTitleText->SetTextContent(const_cast<WCHAR*>(L"Effect Sound Volume "));
		//m_EffectTitleText->CreateRectangle();
	}

	WCHAR TempText[64] = L"";
	wsprintf(TempText, L"%d X %d", extGameOption->GetWidth(), extGameOption->GetHeight());
	m_ScreenText->SetTextContent(TempText);

	_stprintf(TempText, L"%.01f", extGameOption->GetBackGroundSoundVolume());
	m_BGMText->SetTextContent(TempText);
	
	_stprintf(TempText, L"%.01f", extGameOption->GetEffectSoundVolume());
	m_EffectText->SetTextContent(TempText);


	return true;
}

bool OptionScene::Render()
{
	m_BackButton->Render();

	m_NextScreenButton->Render();
	m_PrevScreenButton->Render();

	m_BGMVolumeDownButton->Render();
	m_BGMVolumeUpButton->Render();

	m_EffectVolumeDownButton->Render();
	m_EffectVolumeUpButton->Render();

	m_FullScreenCheckBox->Render();

	m_SettingButton->Render();

	m_ScreenText->Render();
	m_BGMText->Render();
	m_EffectText->Render();
	m_FullScreenText->Render();

	m_ScreenTitleText->Render();
	m_BGMTitleText->Render();
	m_EffectTitleText->Render();

	return true;
}

bool OptionScene::Update()
{
	WCHAR TempText[64] = L"";
	if (m_ScreenText->IsChange())
	{
		wsprintf(TempText, L"%d X %d", m_SupportWindow.CurrentScreen().first, m_SupportWindow.CurrentScreen().second);
		m_ScreenText->SetTextContent(TempText);
	}

	if (m_BGMText->IsChange())
	{
		_stprintf(TempText, L"%.01f", extGameOption->GetBackGroundSoundVolume());
		m_BGMText->SetTextContent(TempText);
	}
	
	if (m_EffectText->IsChange())
	{
		_stprintf(TempText, L"%.01f", extGameOption->GetEffectSoundVolume());
		m_EffectText->SetTextContent(TempText);
	}

	return true;
}

bool OptionScene::Release()
{
	SAFE_RELEASE_AND_DELETE(m_EffectTitleText);
	SAFE_RELEASE_AND_DELETE(m_BGMTitleText);
	SAFE_RELEASE_AND_DELETE(m_ScreenTitleText);

	SAFE_RELEASE_AND_DELETE(m_FullScreenText);
	SAFE_RELEASE_AND_DELETE(m_EffectText);
	SAFE_RELEASE_AND_DELETE(m_BGMText);
	SAFE_RELEASE_AND_DELETE(m_ScreenText);

	SAFE_RELEASE_AND_DELETE(m_FullScreenCheckBox);
	SAFE_RELEASE_AND_DELETE(m_SettingButton);
	SAFE_RELEASE_AND_DELETE(m_EffectVolumeDownButton);
	SAFE_RELEASE_AND_DELETE(m_EffectVolumeUpButton);
	SAFE_RELEASE_AND_DELETE(m_BGMVolumeDownButton);
	SAFE_RELEASE_AND_DELETE(m_BGMVolumeUpButton);
	SAFE_RELEASE_AND_DELETE(m_PrevScreenButton);
	SAFE_RELEASE_AND_DELETE(m_NextScreenButton);
	SAFE_RELEASE_AND_DELETE(m_BackButton);

	return true;
}

void OptionScene::OptionChange(HWND hWnd)
{
	// 모든 요소(Direct2d 및 Direct3d에 관련된 모든 것)를 초기화 한다.
	RECT rt = { 0, 0, m_SupportWindow.CurrentScreen().first, m_SupportWindow.CurrentScreen().second };

	extGameOption->SetWidth(m_SupportWindow.CurrentScreen().first);
	extGameOption->SetHeight(m_SupportWindow.CurrentScreen().second);


	SetWindowPos(hWnd, NULL, CW_USEDEFAULT, CW_USEDEFAULT, rt.right - rt.left, rt.bottom - rt.top, SWP_NOZORDER | SWP_NOMOVE);

	AdjustWindowRect(&rt, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);

	SetWindowPos(hWnd, NULL, CW_USEDEFAULT, CW_USEDEFAULT, rt.right - rt.left, rt.bottom - rt.top, SWP_NOZORDER | SWP_NOMOVE);

	extEngine->Release();
	extEngine->GetD3DEngine()->Release();
	if (!extEngine->GetD3DEngine()->Initialize(extGameOption->GetWidth(), extGameOption->GetHeight(), hWnd, extGameOption->GetFullScreen()))
	{
#ifndef _DEBUG
		MessageBox(hWnd, L"Cannot Resize D3D.", L"Error", MB_OK);
#endif
		return;
	}

	if (!extEngine->Initialize(extEngine->GetD3DEngine(), hWnd, extGameOption, extGameOption->GetFullScreen()))
	{
#ifndef _DEBUG
		MessageBox(hWnd, L"Cannot Initialize D2D.", L"Error", MB_OK);
#endif
		return;
	}

	SceneManager::instance().OnResize();

	this->Release();
	this->Initialize(extEngine, extAudioEngine, extGameOption);
}

LRESULT OptionScene::SceneProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);

	switch (message)
	{
	case WM_MOUSEMOVE:
		if (m_BackButton->IsInside(pt.x, pt.y))
		{
			m_BackButton->Touched();
			break;
		}
		else
			m_BackButton->Normally();

		if (m_PrevScreenButton->IsInside(pt.x, pt.y))
		{
			m_PrevScreenButton->Touched();
			break;
		}
		else
			m_PrevScreenButton->Normally();

		if (m_NextScreenButton->IsInside(pt.x, pt.y))
		{
			m_NextScreenButton->Touched();
			break;
		}
		else
			m_NextScreenButton->Normally();

		if (m_BGMVolumeDownButton->IsInside(pt.x, pt.y))
		{
			m_BGMVolumeDownButton->Touched();
			break;
		}
		else
			m_BGMVolumeDownButton->Normally();

		if (m_BGMVolumeUpButton->IsInside(pt.x, pt.y))
		{
			m_BGMVolumeUpButton->Touched();
			break;
		}
		else
			m_BGMVolumeUpButton->Normally();

		if (m_EffectVolumeDownButton->IsInside(pt.x, pt.y))
		{
			m_EffectVolumeDownButton->Touched();
			break;
		}
		else
			m_EffectVolumeDownButton->Normally();

		if (m_EffectVolumeUpButton->IsInside(pt.x, pt.y))
		{
			m_EffectVolumeUpButton->Touched();
			break;
		}
		else
			m_EffectVolumeUpButton->Normally();

		if (m_FullScreenCheckBox->IsInside(pt.x, pt.y))
		{
			m_FullScreenCheckBox->Touched();
			break;
		}
		else
			m_FullScreenCheckBox->Normally();

		if (m_SettingButton->IsInside(pt.x, pt.y) && IsChange)
		{
			m_SettingButton->Touched();
			break;
		}
		else
			m_SettingButton->Normally();

		break;
	case WM_LBUTTONDOWN: // Mouse Click & Event
		if (m_BackButton->IsInside(pt.x, pt.y))
		{
			m_BackButton->Pressed();
			break;
		}

		if (m_PrevScreenButton->IsInside(pt.x, pt.y))
		{
			m_PrevScreenButton->Pressed();
			break;
		}

		if (m_NextScreenButton->IsInside(pt.x, pt.y))
		{
			m_NextScreenButton->Pressed();
			break;
		}

		if (m_BGMVolumeDownButton->IsInside(pt.x, pt.y))
		{
			m_BGMVolumeDownButton->Pressed();
			break;
		}

		if (m_BGMVolumeUpButton->IsInside(pt.x, pt.y))
		{
			m_BGMVolumeUpButton->Pressed();
			break;
		}

		if (m_EffectVolumeDownButton->IsInside(pt.x, pt.y))
		{
			m_EffectVolumeDownButton->Pressed();
			break;
		}

		if (m_EffectVolumeUpButton->IsInside(pt.x, pt.y))
		{
			m_EffectVolumeUpButton->Pressed();
			break;
		}

		if (m_FullScreenCheckBox->IsInside(pt.x, pt.y))
		{
			m_FullScreenCheckBox->Pressed();
			break;
		}

		if (m_SettingButton->IsInside(pt.x, pt.y) & IsChange)
		{
			m_SettingButton->Pressed();
			break;
		}

		break;
	case WM_LBUTTONUP: // 버튼 이벤트 처리
		if (m_BackButton->IsInside(pt.x, pt.y))
		{
			m_BackButton->Touched();
			SceneManager::instance().EventListen(m_BackButton->GetEvent());
			break;
		}

		if (m_PrevScreenButton->IsInside(pt.x, pt.y))
		{
			m_PrevScreenButton->Touched();
			m_SupportWindow.PrevScreen();
			m_ScreenText->Change();
			SceneManager::instance().EventListen(m_PrevScreenButton->GetEvent());
			IsChange = true;
			break;
		}

		if (m_NextScreenButton->IsInside(pt.x, pt.y))
		{
			m_NextScreenButton->Touched();
			m_SupportWindow.NextScreen();
			m_ScreenText->Change();
			IsChange = true;
			break;
		}

		if (m_BGMVolumeDownButton->IsInside(pt.x, pt.y))
		{
			m_BGMVolumeDownButton->Touched();
			extGameOption->SetBackGroundSoundValue(extGameOption->GetBackGroundSoundVolume() - 0.1f);
			m_BGMText->Change();
			SceneManager::instance().EventListen(m_BGMVolumeDownButton->GetEvent());
			break;
		}

		if (m_BGMVolumeUpButton->IsInside(pt.x, pt.y))
		{
			m_BGMVolumeUpButton->Touched();
			extGameOption->SetBackGroundSoundValue(extGameOption->GetBackGroundSoundVolume() + 0.1f);
			m_BGMText->Change();
			SceneManager::instance().EventListen(m_BGMVolumeUpButton->GetEvent());
			break;
		}

		if (m_EffectVolumeDownButton->IsInside(pt.x, pt.y))
		{
			m_EffectVolumeDownButton->Touched();
			extGameOption->SetEffectSoundValue(extGameOption->GetEffectSoundVolume() - 0.1f);
			m_EffectText->Change();
			SceneManager::instance().EventListen(m_EffectVolumeDownButton->GetEvent());
			break;
		}

		if (m_EffectVolumeUpButton->IsInside(pt.x, pt.y))
		{
			m_EffectVolumeUpButton->Touched();
			extGameOption->SetEffectSoundValue(extGameOption->GetEffectSoundVolume() + 0.1f);
			m_EffectText->Change();
			SceneManager::instance().EventListen(m_EffectVolumeUpButton->GetEvent());
			break;
		}

		if (m_FullScreenCheckBox->IsInside(pt.x, pt.y))
		{
			m_FullScreenCheckBox->Touched();
			IsChange = true;
			break;
		}

		if (m_SettingButton->IsInside(pt.x, pt.y) & IsChange)
		{
			m_SettingButton->Touched();
			this->OptionChange(hWnd);
			IsChange = false;
			break;
		}
		break;
	}
	return 0;
}