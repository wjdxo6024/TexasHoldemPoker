#include "MainMenuButton.h"

MainMenuButton::MainMenuButton()
{

}

MainMenuButton::MainMenuButton(const MainMenuButton& other)
{

}

MainMenuButton::~MainMenuButton()
{

}

bool MainMenuButton::InitializeEx(Direct2DEngine* D2DEngine, int x, int y, int width, int height, WCHAR* text)
{
	Button::Initialize(D2DEngine, x, y, width, height);

	this->CreateText(text);
	this->GetText()->SetTextWidthAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
	this->GetText()->SetTextHeightAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	this->CreateShape(_SHAPE_RECTANGLE);
	reinterpret_cast<CRectangle*>(this->GetShape())->SetFill(true);

	m_NormalColor = D2D1::ColorF(0.1f, 0.5f, 0.5f, 0.7f);
	m_PressColor = D2D1::ColorF(0.05f, 0.25f, 0.25f, 0.7f);
	m_TouchColor = D2D1::ColorF(0.2f, 0.6f, 0.6f, 0.7f);
	reinterpret_cast<CRectangle*>(this->GetShape())->SetColor(m_NormalColor);
	reinterpret_cast<CRectangle*>(this->GetShape())->SetFillColor(m_NormalColor);

	return true;
}

// Button State
void MainMenuButton::Normally() // 평상시
{
	reinterpret_cast<CRectangle*>(this->GetShape())->SetColor(m_NormalColor);
	reinterpret_cast<CRectangle*>(this->GetShape())->SetFillColor(m_NormalColor);
}

void MainMenuButton::Pressed() // 누를시
{
	reinterpret_cast<CRectangle*>(this->GetShape())->SetColor(m_PressColor);
	reinterpret_cast<CRectangle*>(this->GetShape())->SetFillColor(m_PressColor);
}

void MainMenuButton::Touched() // 마우스가 버튼 위에 존재할 때
{
	reinterpret_cast<CRectangle*>(this->GetShape())->SetColor(m_TouchColor);
	reinterpret_cast<CRectangle*>(this->GetShape())->SetFillColor(m_TouchColor);
}

void MainMenuButton::Selected() // 버튼 선택시
{

}

void MainMenuButton::Disabled() // 버튼 비선택시
{

}