#ifndef _SHAPE_H_
#define _SHAPE_H_
#include "../Direct2DEngine.h"
#include <memory>
#include <wrl/client.h>

#define _SHAPE_BASIC 0
#define _SHAPE_RECTANGLE 1
#define _SHAPE_ELLIPSE 2

// ��� ������ �⺻ Ŭ����
class Shape
{
protected:
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_shapeBrush;
	D2D1::ColorF m_ShapeLineColor = D2D1::ColorF::White;
	int shape_X, shape_Y;
	int m_width, m_height;

	D2D1_POINT_2F m_CenterPos;
	D2D1_SIZE_F m_RenderSize;
	float m_RotationDegree;
	Direct2DEngine* m_pD2DEngine = NULL;

public:
	Shape();
	Shape(const Shape& other);
	~Shape();

	virtual bool Initialize(Direct2DEngine* pD2DEngine, int x, int y, int width, int height);
	virtual bool Draw();
	virtual bool DrawDirect(float x, float y);
	virtual bool Update();
	virtual void Release();

	virtual void SetColor(D2D1::ColorF color);
	virtual void SetPosition(int x, int y); // TODO : ȸ���� ��� �ٸ� ��ҵ��� ������.
	virtual void SetRotationDegree(float Degree);
	
};

#endif

