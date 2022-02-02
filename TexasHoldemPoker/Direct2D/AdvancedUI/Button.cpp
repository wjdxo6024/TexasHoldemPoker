#include "Button.h"

Button::Button()
{
	m_Text = NULL;
	m_Bitmap = NULL;
	m_Shape = NULL;

	m_ButtonEvent = ButtonEvent::ButtonEvent_Empty;
}

Button::Button(const Button& other)
{

}

Button::~Button()
{
	this->Release();
}

bool Button::Initialize(Direct2DEngine* D2DEngine, int x, int y, int width, int height)
{
	extD2DEngine = D2DEngine;

	m_Area.InitializeA(x, y, width, height);
	return true;
}

bool Button::Update()
{
	return true;
}

bool Button::Render()
{
	if (m_Bitmap != NULL)
	{
		m_Bitmap->Draw();
	}

	if (m_Shape != NULL)
	{
		m_Shape->Draw();
	}

	if (m_Text != NULL)
	{
		m_Text->DrawDirectInRect(m_Area.GetRect());
	}

	return true;
}

bool Button::Release()
{
	if (m_Shape != NULL)
	{
		m_Shape->Release();
		delete m_Shape;
		m_Shape = 0;
	}

	if (m_Bitmap != NULL)
	{
		m_Bitmap->Release();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	if (m_Text != NULL)
	{
		m_Text->Release();
		delete m_Text;
		m_Text = 0;
	}
	return true;
}

bool Button::AreaResize(int width, int height)
{
	m_Area.AreaResize(width, height);
	return true;
}

void Button::SetWidth(int width)
{
	m_Area.GetTransform()->SetWidth(width);
	m_Area.AreaUpdate();
}

int Button::GetWidth()
{
	return m_Area.GetTransform()->GetWidth();
}

void Button::SetHeight(int height)
{
	m_Area.GetTransform()->SetHeight(height);
	m_Area.AreaUpdate();
}

int Button::GetHeight()
{
	return m_Area.GetTransform()->GetHeight();
}

void Button::CreateText(const WCHAR* text)
{
	m_Text = new Text;
	if (m_Text == NULL)
		return;

	if (!m_Text->Initialize(extD2DEngine, const_cast<WCHAR*>(text)))
	{
		m_Text->Release();
		delete m_Text;
		m_Text = NULL;
	}
}

void Button::CreateBitmap(const WCHAR* bitmap)
{
	m_Bitmap = new CBitmap;
	if (m_Bitmap == NULL)
		return;

	if (!m_Bitmap->Initialize(extD2DEngine, m_Area.GetTransform()->GetPosX(), m_Area.GetTransform()->GetPosY(),
		m_Area.GetTransform()->GetWidth(), m_Area.GetTransform()->GetHeight(), const_cast<WCHAR*>(bitmap)))
	{
		m_Bitmap->Release();
		delete m_Bitmap;
		m_Bitmap = NULL;
	}
}

void Button::CreateShape(int shape)
{
	SAFE_RELEASE_AND_DELETE(m_Shape);

	if (shape == _SHAPE_BASIC)
		m_Shape = new Shape();
	else if (shape == _SHAPE_RECTANGLE)
		m_Shape = new CRectangle();
	else if (shape == _SHAPE_ELLIPSE)
		m_Shape = new CEllipse();
	
	m_Shape->Initialize(extD2DEngine, m_Area.GetTransform()->GetPosX(), m_Area.GetTransform()->GetPosY(),
		m_Area.GetTransform()->GetWidth(), m_Area.GetTransform()->GetHeight());
	return;
}

Text* Button::GetText()
{
	return m_Text;
}

CBitmap* Button::GetBitmap()
{
	return m_Bitmap;
}

Shape* Button::GetShape()
{
	return m_Shape;
}

void Button::SetEvent(ButtonEvent Event)
{
	m_ButtonEvent = Event;
}

ButtonEvent Button::GetEvent()
{
	return m_ButtonEvent;
}

void Button::OnClick()
{
	Button::OnClick();
}

bool Button::IsInside(int x, int y)
{
	return m_Area.IsInside(x, y);
}

void Button::Normally() // 평상시
{

}

void Button::Pressed() // 누를시
{
	
}

void Button::Touched() // 마우스가 버튼 위에 존재할 때
{

}

void Button::Selected() // 버튼 선택시
{

}

void Button::Disabled() // 버튼 비선택시
{

}