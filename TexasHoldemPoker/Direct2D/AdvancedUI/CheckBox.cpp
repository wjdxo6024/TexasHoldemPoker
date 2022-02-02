#include "CheckBox.h"

CheckBox::CheckBox()
{
	m_BackGround = NULL;
	m_CheckRectangle = NULL;
	m_IsCheck = false;
}

CheckBox::CheckBox(const CheckBox& other)
{

}

CheckBox::~CheckBox()
{
	this->Release();
}

bool CheckBox::Initialize(Direct2DEngine* D2DEngine, int x, int y, int width, int height)
{
	extEngine = D2DEngine;

	m_NormalColor = D2D1::ColorF(0.1f, 0.5f, 0.5f, 0.7f);
	m_PressColor = D2D1::ColorF(0.05f, 0.25f, 0.25f, 0.7f);
	m_TouchColor = D2D1::ColorF(0.2f, 1.0f, 1.0f, 0.7f);

	m_BackGround = new CRectangle;
	if (m_BackGround != NULL)
	{
		m_BackGround->Initialize(extEngine, x, y, width, height);
		m_BackGround->SetFill(true);
		m_BackGround->SetColor(D2D1::ColorF(0.1f / 4, 0.5f / 4, 0.5f / 4, 0.7f));
		m_BackGround->SetStroke(5.0f);
		m_BackGround->SetFillColor(m_NormalColor);
	}

	m_CheckRectangle = new CRectangle;
	if (m_CheckRectangle != NULL)
	{
		m_CheckRectangle->Initialize(extEngine, x + (x / 4), y + (y / 4), width / 2, height / 2);
		m_CheckRectangle->SetFill(true);
		m_CheckRectangle->SetColor(D2D1::ColorF(0.05f, 0.25f, 0.25f, 0.7f));
		m_CheckRectangle->SetFillColor(D2D1::ColorF(0.05f, 0.25f, 0.25f, 0.7f));
	}

	return true;
}

bool CheckBox::Render()
{
	if(m_BackGround != NULL)
		m_BackGround->Draw();

	if(m_IsCheck && m_CheckRectangle != NULL)
		m_CheckRectangle->Draw();

	return true;
}

bool CheckBox::Update()
{
	return true;
}

bool CheckBox::Release()
{
	SAFE_RELEASE_AND_DELETE(m_BackGround);
	SAFE_RELEASE_AND_DELETE(m_CheckRectangle);

	return true;
}

bool CheckBox::AreaResize(int width, int height)
{
	m_Area.AreaResize(width, height);
	return true;
}

bool CheckBox::IsInside(int x, int y)
{
	return m_Area.IsInside(x, y);
}

void CheckBox::Check()
{
	if (m_IsCheck)
		m_IsCheck = false;
	else
		m_IsCheck = true;
}

bool CheckBox::GetCheck()
{
	return m_IsCheck;
}

void CheckBox::SetCheck(bool check)
{
	m_IsCheck = check;
}

void CheckBox::Normally() // 평상시
{
	m_BackGround->SetFillColor(m_NormalColor);
}

void CheckBox::Pressed() // 누를시
{
	m_BackGround->SetFillColor(m_PressColor);
}

void CheckBox::Touched() // 마우스가 버튼 위에 존재할 때
{
	m_BackGround->SetFillColor(m_TouchColor);
}

void CheckBox::Selected() // 버튼 선택시
{

}

void CheckBox::Disabled() // 버튼 비선택시
{

}