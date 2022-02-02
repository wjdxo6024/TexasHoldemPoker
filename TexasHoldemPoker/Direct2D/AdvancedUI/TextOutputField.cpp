#include "TextOutputField.h"

TextOutputField::TextOutputField()
{
	m_BackgroundImage = NULL;
	m_BackgroundRect = NULL;
	m_Text = NULL;
}

TextOutputField::TextOutputField(const TextOutputField& other)
{

}

TextOutputField::~TextOutputField()
{

}

bool TextOutputField::Initialize(Direct2DEngine* D2DEngine, int x, int y, int width, int height)
{
	extEngine = D2DEngine;
	m_Area.InitializeA(x, y, width, height);
	m_Text = new Text;
	m_Text->Initialize(extEngine, const_cast<WCHAR*>(L""));
	return true;
}

bool TextOutputField::Render()
{
	if (m_BackgroundImage != NULL)
		m_BackgroundImage->Draw();

	if (m_BackgroundRect != NULL)
		m_BackgroundRect->Draw();

	RECT rt = { m_Area.GetRect().left + m_TextIntervalWidth, m_Area.GetRect().top + m_TextIntervalHeight,
	m_Area.GetRect().right + m_TextIntervalWidth, m_Area.GetRect().bottom + m_TextIntervalHeight };
	m_Text->DrawDirectInRect(rt);
	return true;
}

bool TextOutputField::Update()
{
	return true;
}

bool TextOutputField::Release()
{
	SAFE_RELEASE_AND_DELETE(m_BackgroundImage);
	SAFE_RELEASE_AND_DELETE(m_BackgroundRect);
	SAFE_RELEASE_AND_DELETE(m_Text);
	return true;
}

bool TextOutputField::CreateImage(WCHAR* filepath)
{
	m_BackgroundImage = new CBitmap;
	if (m_BackgroundImage != NULL)
	{
		m_BackgroundImage->Initialize(extEngine, m_Area.GetTransform()->GetPosX(), m_Area.GetTransform()->GetPosY(),
			m_Area.GetTransform()->GetWidth(), m_Area.GetTransform()->GetHeight(), filepath);
	}
	else
	{
		SAFE_DELETE(m_BackgroundImage);
		return false;
	}

	return true;
}

CBitmap* TextOutputField::GetImage()
{
	return m_BackgroundImage;
}

bool TextOutputField::CreateRectangle()
{
	m_BackgroundRect = new CRectangle;
	if (m_BackgroundRect != NULL)
	{
		m_BackgroundRect->Initialize(extEngine, m_Area.GetTransform()->GetPosX(), m_Area.GetTransform()->GetPosY(),
			m_Area.GetTransform()->GetWidth(), m_Area.GetTransform()->GetHeight());
	}
	else
	{
		SAFE_DELETE(m_BackgroundRect);
		return false;
	}

	return true;
}
CRectangle* TextOutputField::GetRect()
{
	return m_BackgroundRect;
}

void TextOutputField::SetTextInterval(int width, int height)
{
	SetTextIntervalWidth(width);
	SetTextIntervalHeight(height);

	
}

void TextOutputField::SetTextIntervalWidth(int width)
{
	m_TextIntervalWidth = width;
}

void TextOutputField::SetTextIntervalHeight(int height)
{
	m_TextIntervalHeight = height;
}

void TextOutputField::SetTextContent(WCHAR* string)
{
	m_TextContent = string;
	m_Text->SetText(const_cast<WCHAR*>(m_TextContent.c_str()));
}

Text* TextOutputField::GetText()
{
	return m_Text;
}