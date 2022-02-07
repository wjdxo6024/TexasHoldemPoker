#include "CRectangle.h"

CRectangle::CRectangle()
{

}

CRectangle::~CRectangle()
{

}

bool CRectangle::Initialize(Direct2DEngine* pD2DEngine, int x, int y, int width, int height)
{
	Shape::Initialize(pD2DEngine, x, y, height, width);
	m_Rect.left = x;
	m_Rect.top = y;
	m_Rect.right = x + width;
	m_Rect.bottom = y + height;

	// Default
	m_LineStroke = 1.0f;
	IsFill = false;
	IsRound = false;
	m_FillColor = D2D1::ColorF::Aqua;

	if (FAILED(m_pD2DEngine->GetDeviceContext()->CreateSolidColorBrush(D2D1::ColorF(m_FillColor), m_FillBrush.GetAddressOf())))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Create Solid Brush.", L"Rectangle Error", MB_OK);
#endif
		return false;
	}

	return true;
}

bool CRectangle::Draw()
{
	Shape::Draw();

	if (IsRound)
	{
		D2D1_ROUNDED_RECT roundRect = { m_Rect, 5.0f, 5.0f };
		m_pD2DEngine->GetDeviceContext()->DrawRoundedRectangle(roundRect, *m_shapeBrush.GetAddressOf(), m_LineStroke);

		if (IsFill)
		{
			m_pD2DEngine->GetDeviceContext()->FillRoundedRectangle(roundRect, *m_FillBrush.GetAddressOf());
		}
	}
	else
	{
		m_pD2DEngine->GetDeviceContext()->DrawRectangle(m_Rect, *m_shapeBrush.GetAddressOf(), m_LineStroke);

		if (IsFill)
		{
			m_pD2DEngine->GetDeviceContext()->FillRectangle(m_Rect, *m_FillBrush.GetAddressOf());
		}

	}

	return true;
}

bool CRectangle::DrawDirect(float x, float y)
{
	return true;
}

bool CRectangle::Update()
{
	return true;
}

void CRectangle::Release()
{

}

void CRectangle::SetFill(bool isFill)
{
	IsFill = isFill;
}

void CRectangle::SetRound(bool isRound)
{
	IsRound = isRound;
}

void CRectangle::SetStroke(float stroke)
{
	m_LineStroke = stroke;
}

void CRectangle::SetFillColor(D2D1::ColorF color)
{
	m_FillColor = color;
	m_FillBrush->SetColor(m_FillColor);
}

void CRectangle::SetPosX(float x)
{
	float beforeWidth = m_Rect.right - m_Rect.left;
	m_Rect.left = x;
	m_Rect.right = x + beforeWidth;
}

void CRectangle::SetPosY(float y)
{
	float beforeHeight = m_Rect.bottom - m_Rect.top;
	m_Rect.top = y;
	m_Rect.bottom = y + beforeHeight;
}

void CRectangle::SetPos(float x, float y)
{
	this->SetPosX(x);
	this->SetPosY(y);
}

void CRectangle::SetWidth(float width)
{
	if (m_Rect.right - m_Rect.left > width)
	{
		m_Rect.right -= (m_Rect.right - width);
	}
	else
	{
		m_Rect.right += (width - m_Rect.right);
	}
}

void CRectangle::SetHeight(float height)
{
	if (m_Rect.bottom - m_Rect.top > height)
	{
		m_Rect.bottom -= (m_Rect.bottom - height);
	}
	else
	{
		m_Rect.bottom += (height - m_Rect.bottom);
	}
}