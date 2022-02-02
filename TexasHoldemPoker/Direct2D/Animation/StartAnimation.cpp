#include "StartAnimation.h"

StartAnimation::StartAnimation()
{
	m_IsAnimate = false;
}

StartAnimation::StartAnimation(const StartAnimation& other)
{

}

StartAnimation::~StartAnimation()
{

}

bool StartAnimation::Initialize(Direct2DEngine* D2DEngine, GameOption* gameOption, AudioEngine* audioEngine)
{
	extD2DEngine = D2DEngine;
	extGameOption = gameOption;
	extAudioEngine = audioEngine;

	m_BannerBackground = new CRectangle;
	if (m_BannerBackground != NULL)
	{
		m_BannerBackground->Initialize(extD2DEngine,
			0, 
			extGameOption->GetHeight() / 2 - MyFunctions::ScalingUI_Y(100, extGameOption->GetHeight()),
			extGameOption->GetWidth(), 
			MyFunctions::ScalingUI_Y(200, extGameOption->GetHeight()));

		m_BannerBackground->SetFill(true);
		m_BannerBackground->SetColor(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f));
		m_BannerBackground->SetFillColor(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f));
	}

	m_TextForDraw = new TextOutputField;
	if (m_TextForDraw != NULL)
	{
		m_TextForDraw->Initialize(extD2DEngine, 0,
			extGameOption->GetHeight() / 2 - MyFunctions::ScalingUI_Y(100, extGameOption->GetHeight()),
			extGameOption->GetWidth(),
			MyFunctions::ScalingUI_Y(200, extGameOption->GetHeight()));

		m_TextForDraw->GetText()->SetTextWidthAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
		m_TextForDraw->GetText()->SetTextHeightAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		m_TextForDraw->GetText()->SetFontColor(D2D1::ColorF(1.0f, 1.0f, 1.0f, 0.0f));
		m_TextForDraw->GetText()->SetFontSize(m_TextForDraw->GetText()->GetFontSize() * 2);
	}

	m_EffectSound = new EffectSound;
	if (m_EffectSound != NULL)
	{
		m_EffectSound->InitializeBasic(L"./Resource/Audio/StartPhase.wav", extAudioEngine, extGameOption);
	}

	return true;
}

bool StartAnimation::Render()
{
	if (m_IsAnimate)
	{
		m_BannerBackground->Draw();
		m_TextForDraw->Render();
	}
	return true;
}

bool StartAnimation::Update(double deltaTime)
{
	if (m_IsAnimate)
	{
		m_TempValue += 1.0 * deltaTime;
		m_AnimationValue = -pow(m_TempValue, 2) + 1.0;

		if (m_AnimationValue <= 0.0f)
		{
			m_IsAnimate = false;
			return false;
		}

		m_BannerBackground->SetColor(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.9f * m_AnimationValue));
		m_BannerBackground->SetFillColor(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.9f * m_AnimationValue));
		m_TextForDraw->GetText()->SetFontColor(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f * m_AnimationValue));
	}

	return true;
}

bool StartAnimation::Release()
{
	SAFE_RELEASE_AND_DELETE(m_EffectSound);
	SAFE_RELEASE_AND_DELETE(m_BannerBackground);
	SAFE_RELEASE_AND_DELETE(m_TextForDraw);

	return true;
}

bool StartAnimation::Start()
{
	m_IsAnimate = true;
	m_TempValue = -0.99f;
	m_AnimationValue = 0.0f;
	m_EffectSound->Play();
	return true;
}

bool StartAnimation::Stop()
{
	if (m_IsAnimate)
		m_IsAnimate = false;
	else
		m_IsAnimate = true;

	return true;
}

bool StartAnimation::SetText(const WCHAR* text)
{
	m_TextForDraw->GetText()->SetText(const_cast<WCHAR*>(text));
	return true;
}

bool StartAnimation::IsAnimate()
{
	return m_IsAnimate;
}