#include "NoticeAnimation.h"

bool NoticeAnimation::Initialize(Direct2DEngine* D2DEngine, GameOption* gameOption)
{
	extEngine = D2DEngine;
	extGameOption = gameOption;

	m_OutputField = new TextOutputField;
	if (m_OutputField != NULL)
	{
		m_OutputField->Initialize(extEngine, extGameOption->GetWidth() / 4,
			ScalingUI_Y(-40, extGameOption->GetHeight()),
			extGameOption->GetWidth() / 2,
			ScalingUI_Y(40, extGameOption->GetHeight()));

		m_OutputField->CreateRectangle();
		m_OutputField->SetTextContent(const_cast<WCHAR*>(L""));
		m_OutputField->GetRect()->SetFill(TRUE);
		m_OutputField->GetRect()->SetColor(D2D1::ColorF::White);
		m_OutputField->GetRect()->SetStroke(2.0f);
		m_OutputField->GetRect()->SetFillColor(D2D1::ColorF::Black);
		m_OutputField->GetText()->SetFontColor(D2D1::ColorF::White);
		m_OutputField->GetText()->SetTextWidthAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
		m_OutputField->GetText()->SetTextHeightAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}
	else
		return false;
	return true;
}

bool NoticeAnimation::Render()
{
	m_OutputField->Render();
	return true;
}

bool NoticeAnimation::Update(float deltaTime)
{
	if (m_MessageQueue.size() > 0 && Is_Animate != true)
	{
		Is_Animate = true;
		m_OutputField->SetTextContent(const_cast<WCHAR*>(m_MessageQueue.front().c_str()));
		m_MessageQueue.pop();
		m_TempValue = -8.0f;
	}

	if (Is_Animate)
	{
		m_TempValue += 10.0f * deltaTime;
		m_AnimationValue = -pow(m_TempValue, 2) + m_OutputField->GetArea().GetTransform()->GetFinalHeight();
		if (m_AnimationValue >= 1.0f)
			m_AnimationValue = 1.0f;

		m_OutputField->SetPosY(m_AnimationValue);

		if (m_AnimationValue <= -m_OutputField->GetArea().GetTransform()->GetFinalHeight() * 1.5)
		{
			Is_Animate = false;
			return false;
		}
	}

	return true;
}

bool NoticeAnimation::Release()
{
	SAFE_RELEASE_AND_DELETE(m_OutputField);
	return true;
}

bool NoticeAnimation::InputMessage(const WCHAR* Message)
{
	std::wstring TempMessage = Message;
	m_MessageQueue.push(TempMessage);
	return true;
}