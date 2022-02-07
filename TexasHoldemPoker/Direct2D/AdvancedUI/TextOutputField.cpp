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
	m_TextRT = { m_Area.GetRect().left + m_TextIntervalWidth, m_Area.GetRect().top + m_TextIntervalHeight,
	m_Area.GetRect().right + m_TextIntervalWidth, m_Area.GetRect().bottom + m_TextIntervalHeight };
	return true;
}

bool TextOutputField::Render()
{
	if (m_BackgroundImage != NULL)
	{
		m_BackgroundImage->Draw();
	}

	if (m_BackgroundRect != NULL)
	{
		m_BackgroundRect->Draw();
	}

	m_Text->DrawDirectInRect(m_TextRT);
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

UIBoxArea& TextOutputField::GetArea()
{
	return m_Area;
}

void TextOutputField::SetPosX(float x)
{
	m_Area.GetTransform()->SetPosX(x);
	m_Area.AreaUpdate();
	if (m_BackgroundImage != NULL)
	{
		m_BackgroundImage->Repos(m_Area.GetTransform()->GetPosX(), m_Area.GetTransform()->GetPosY());
	}

	if (m_BackgroundRect != NULL)
	{
		m_BackgroundRect->SetPos(m_Area.GetTransform()->GetPosX(), m_Area.GetTransform()->GetPosY());
	}
	this->UpdateTextRect();
}

void TextOutputField::SetPosY(float y)
{
	m_Area.GetTransform()->SetPosY(y);
	m_Area.AreaUpdate();
	if (m_BackgroundImage != NULL)
	{
		m_BackgroundImage->Repos(m_Area.GetTransform()->GetPosX(), m_Area.GetTransform()->GetPosY());
	}

	if (m_BackgroundRect != NULL)
	{
		m_BackgroundRect->SetPos(m_Area.GetTransform()->GetPosX(), m_Area.GetTransform()->GetPosY());
	}
	this->UpdateTextRect();
}

void TextOutputField::SetPos(float x, float y)
{
	this->SetPosX(x);
	this->SetPosY(y);
}

void TextOutputField::SetWidth(float width)
{
	m_Area.GetTransform()->SetWidth(width);
	m_Area.AreaUpdate();

	if (m_BackgroundImage != NULL)
	{
		m_BackgroundImage->OnResize(extEngine, m_Area.GetTransform()->GetFinalWidth(), m_Area.GetTransform()->GetFinalHeight());
	}

	if (m_BackgroundRect != NULL)
	{
		m_BackgroundRect->SetWidth(m_Area.GetTransform()->GetFinalWidth());
	}

	this->UpdateTextRect();
}

void TextOutputField::SetHeight(float height)
{
	m_Area.GetTransform()->SetHeight(height);
	m_Area.AreaUpdate();

	if (m_BackgroundImage != NULL)
	{
		m_BackgroundImage->OnResize(extEngine, m_Area.GetTransform()->GetFinalWidth(), m_Area.GetTransform()->GetFinalHeight());
	}

	if (m_BackgroundRect != NULL)
	{
		m_BackgroundRect->SetHeight(m_Area.GetTransform()->GetFinalHeight());
	}
	this->UpdateTextRect();
}

void TextOutputField::UpdateTextRect()
{
	m_TextRT = { m_Area.GetRect().left + m_TextIntervalWidth, m_Area.GetRect().top + m_TextIntervalHeight,
	m_Area.GetRect().right + m_TextIntervalWidth, m_Area.GetRect().bottom + m_TextIntervalHeight };
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

	this->UpdateTextRect();
}

void TextOutputField::SetTextIntervalHeight(int height)
{
	m_TextIntervalHeight = height;

	this->UpdateTextRect();
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