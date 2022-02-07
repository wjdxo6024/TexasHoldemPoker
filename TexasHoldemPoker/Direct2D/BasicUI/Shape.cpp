#include "Shape.h"

Shape::Shape()
{
	
}

Shape::Shape(const Shape& other)
{

}

Shape::~Shape()
{

}

bool Shape::Initialize(Direct2DEngine* pD2DEngine, int x, int y, int width, int height)
{
	m_pD2DEngine = pD2DEngine;
	shape_X = x;
	shape_Y = y;
	m_width = width;
	m_height = height;

	// Default
	m_RenderSize = m_pD2DEngine->GetDeviceContext()->GetSize();
	m_CenterPos.x = (x + width / 2);
	m_CenterPos.y = (y + height / 2);
	m_RotationDegree = 0.0f;

	m_ShapeLineColor = D2D1::ColorF::Aqua; // Default

	if (FAILED(m_pD2DEngine->GetDeviceContext()->CreateSolidColorBrush(D2D1::ColorF(m_ShapeLineColor), m_shapeBrush.GetAddressOf())))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Create Solid Brush.", L"Shape Error", MB_OK);
#endif
		return false;
	}
}

bool Shape::Draw()
{
	m_pD2DEngine->GetDeviceContext()->SetTransform(D2D1::IdentityMatrix());
	return true;
}

bool Shape::DrawDirect(float x, float y)
{
	m_pD2DEngine->GetDeviceContext()->SetTransform(D2D1::IdentityMatrix());
	return true;
}

bool Shape::Update()
{
	return true;
}

void Shape::Release()
{

}

void Shape::SetColor(D2D1::ColorF color)
{
	m_ShapeLineColor = color;
	m_shapeBrush->SetColor(m_ShapeLineColor);
}

void Shape::SetPos(int x, int y)
{

}

void Shape::SetRotationDegree(float Degree)
{
	m_RotationDegree = Degree;
}