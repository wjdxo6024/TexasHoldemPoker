#include "Text.h"

Text::Text()
{
	m_FontSize = 20.0f;
	m_WidthAlign = DWRITE_TEXT_ALIGNMENT_LEADING;
	m_HeightAlign = DWRITE_PARAGRAPH_ALIGNMENT_NEAR;
	m_IsBold = false;
	m_Style = DWRITE_FONT_STYLE_NORMAL;
	m_Weight = DWRITE_FONT_WEIGHT_LIGHT;
	m_Stretch = DWRITE_FONT_STRETCH_NORMAL;
}

Text::Text(const Text& other)
{

}

Text::~Text()
{
	
}

bool Text::Initialize(Direct2DEngine* D2DEngine, WCHAR* String)
{
	m_pD2DEngine = D2DEngine;
	m_TextContents = String;

	if (FAILED(D2DEngine->GetWriteFactory()->CreateTextFormat(L"Arial", NULL, m_Weight, m_Style, m_Stretch, m_FontSize, L"ko-KR", m_textFormat.GetAddressOf())))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Create Solid Brush.", L"Text Error", MB_OK);
#endif
		return false;
	}

	// TODO : TextLayout이기 때문에 어느정도 문자가 들어가고 그 다음 줄이 바뀌는지 알아 볼 것.
	if (FAILED(m_pD2DEngine->GetWriteFactory()->CreateTextLayout(String, wcslen(String) + 1, m_textFormat.Get(), (float)m_pD2DEngine->GetScreenWidth(), (float)D2DEngine->GetScreenHeight(), m_textLayout.GetAddressOf())))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Create Solid Brush.", L"Text Error", MB_OK);
#endif
		return false;
	}
	if (FAILED(m_pD2DEngine->GetDeviceContext()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), m_TextBrush.GetAddressOf())))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Create Solid Brush.", L"Text Error", MB_OK);
#endif
		return false;
	}

	return true;
}

bool Text::Draw(float x, float y)
{
	m_pD2DEngine->GetDeviceContext()->DrawTextLayout(D2D1::Point2F(x, y), m_textLayout.Get(), m_TextBrush.Get());
	return true;
}

bool Text::DrawDirect(float x, float y)
{
	m_pD2DEngine->GetDeviceContext()->SetTransform(D2D1::IdentityMatrix());
	// 사각형 영역 계산을 잘할 것.
	D2D1_RECT_F r = { x , y , x + (m_TextContents.size() + 1) * 12 , y + 20 };

	m_textLayout->SetMaxHeight(r.bottom - r.top);
	m_textLayout->SetMaxWidth(r.right - r.left);
	this->Draw(r.left, r.top);
	return true;
}

bool Text::DrawDirectInRect(RECT rt)
{
	m_pD2DEngine->GetDeviceContext()->SetTransform(D2D1::IdentityMatrix());
	m_textLayout->SetMaxHeight(rt.bottom - rt.top);
	m_textLayout->SetMaxWidth(rt.right - rt.left);
	this->Draw(rt.left, rt.top);
	return true;
}

bool Text::DrawDirectWithString(float x, float y, WCHAR* String)
{
	m_pD2DEngine->GetDeviceContext()->SetTransform(D2D1::IdentityMatrix());
	// 사각형 영역 계산을 잘할 것.
	int stringlength = wcslen(String) + 1;
	D2D1_RECT_F r = { x , y , x + stringlength * 12 , y + 20 };
	m_pD2DEngine->GetDeviceContext()->DrawTextW(String, stringlength, m_textFormat.Get(), &r, m_TextBrush.Get());

	return true;
}

// 사용하지 않음
bool Text::Update()
{
	return true;
}

// 사용하지 않음
void Text::Release()
{

}

void Text::SetPosition(float x, float y)
{

}

void Text::SetFontStyle(DWRITE_FONT_STYLE fontStyle)
{
	DWRITE_TEXT_RANGE range;
	range.length = m_TextContents.size();
	range.startPosition = 0;
	m_Style = fontStyle;
	m_textLayout->SetFontStyle(m_Style, range);
}

void Text::SetFontEffect(const char* fonteffect)
{

}

void Text::SetFontWeight(DWRITE_FONT_WEIGHT weight)
{
	DWRITE_TEXT_RANGE range;
	range.length = m_TextContents.size();
	range.startPosition = 0;
	m_Weight = weight;
	m_textLayout->SetFontWeight(m_Weight, range);
}

void Text::SetFontBold(bool isBold)
{
	DWRITE_TEXT_RANGE range;
	range.length = m_TextContents.size();
	range.startPosition = 0;
	m_IsBold = isBold;
	if (m_IsBold)
		m_textLayout->SetFontWeight(DWRITE_FONT_WEIGHT_BOLD, range);
	else
		m_textLayout->SetFontWeight(DWRITE_FONT_WEIGHT_NORMAL, range);
}

void Text::SetFontSize(float fontSize)
{
	DWRITE_TEXT_RANGE range;
	range.length = m_TextContents.size();
	range.startPosition = 0;
	m_FontSize = fontSize;
	m_textLayout->SetFontSize(m_FontSize, range);
}

float Text::GetFontSize()
{
	return m_textLayout->GetFontSize();
}

void Text::SetFontColor(D2D1::ColorF color)
{
	m_TextBrush->SetColor(color);
}

D2D1_COLOR_F Text::GetFontColor()
{
	return m_TextBrush->GetColor();
}

void Text::SetTextWidthAlign(DWRITE_TEXT_ALIGNMENT textAlign)
{
	m_WidthAlign = textAlign;
	m_textLayout->SetTextAlignment(m_WidthAlign);
}

void Text::SetTextHeightAlign(DWRITE_PARAGRAPH_ALIGNMENT textAlign)
{
	m_HeightAlign = textAlign;
	m_textLayout->SetParagraphAlignment(m_HeightAlign);
}

void Text::SetText(WCHAR* string)
{
	m_TextContents = string;
	m_textLayout->Release();

	if (FAILED(m_pD2DEngine->GetWriteFactory()->CreateTextLayout(m_TextContents.c_str(), m_TextContents.size() + 1, m_textFormat.Get(), (float)m_pD2DEngine->GetScreenWidth(), (float)m_pD2DEngine->GetScreenHeight(), m_textLayout.GetAddressOf())))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Create Text Layout.", L"Text Error", MB_OK);
#endif
	}

	this->SetFontSize(m_FontSize);
	this->SetFontWeight(m_Weight);
	this->SetFontBold(m_IsBold);
	this->SetFontStyle(m_Style);
	this->SetTextWidthAlign(m_WidthAlign);
	this->SetTextHeightAlign(m_HeightAlign);
	return;
}