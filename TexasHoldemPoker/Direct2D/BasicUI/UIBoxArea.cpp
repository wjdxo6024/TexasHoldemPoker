#include "UIBoxArea.h"

UIBoxArea::UIBoxArea()
{

}

UIBoxArea::UIBoxArea(const UIBoxArea& other)
{

}

UIBoxArea::~UIBoxArea()
{

}

void UIBoxArea::AreaUpdate()
{
	m_BoxArea.left = m_RectTransform.GetPosX();
	m_BoxArea.right = m_RectTransform.GetPosX() + m_RectTransform.GetWidth();
	m_BoxArea.top = m_RectTransform.GetPosY();
	m_BoxArea.bottom = m_RectTransform.GetPosY() + m_RectTransform.GetHeight();
}

void UIBoxArea::AreaResize(int WindowWidth, int WindowHeight)
{
	m_RectTransform.SetPosX(MyFunctions::ScalingUI_X(m_RectTransform.GetPosX(), WindowWidth));
	m_RectTransform.SetPosY(MyFunctions::ScalingUI_Y(m_RectTransform.GetPosY(), WindowHeight));

	m_RectTransform.SetWidth(MyFunctions::ScalingUI_X(m_RectTransform.GetWidth(), WindowWidth));
	m_RectTransform.SetHeight(MyFunctions::ScalingUI_Y(m_RectTransform.GetHeight(), WindowHeight));

	this->AreaUpdate();
}

void UIBoxArea::Initialize(int left, int right, int top, int bottom)
{
	m_RectTransform.SetPosX(left);
	m_RectTransform.SetPosY(top);

	m_RectTransform.SetHeight(bottom - top);
	m_RectTransform.SetWidth(right - left);

	AreaUpdate();

	//
}

void UIBoxArea::Initialize(RECT rect)
{
	m_RectTransform.SetPosX(rect.left);
	m_RectTransform.SetPosY(rect.top);

	m_RectTransform.SetHeight(rect.bottom - rect.top);
	m_RectTransform.SetWidth(rect.right - rect.left);

	AreaUpdate();
}

void UIBoxArea::InitializeA(int x, int y, int width, int height)
{
	m_RectTransform.SetPosX(x);
	m_RectTransform.SetPosY(y);
	m_RectTransform.SetWidth(width);
	m_RectTransform.SetHeight(height);

	AreaUpdate();
}

void UIBoxArea::InitializeUsingPoint(int startX, int startY, int endX, int endY)
{
	m_RectTransform.SetPosX(startX);
	m_RectTransform.SetPosY(startY);

	m_RectTransform.SetHeight(endY - startY);
	m_RectTransform.SetWidth(endX - startX);

	AreaUpdate();
}

bool UIBoxArea::IsInside(int x, int y)
{
	if (x >= m_BoxArea.left && x <= m_BoxArea.right && y >= m_BoxArea.top && y <= m_BoxArea.bottom)
		return true;
	else
		return false;
}

RectTransform* UIBoxArea::GetTransform()
{
	return &m_RectTransform;
}

RECT UIBoxArea::GetRect()
{
	AreaUpdate();
	return m_BoxArea;
}