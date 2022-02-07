#pragma once
#include "Shape.h"
class CRectangle :
	public Shape
{
protected:
	D2D1_RECT_F m_Rect;
	D2D1::ColorF m_FillColor = NULL;
	Microsoft::WRL::ComPtr<ID2D1StrokeStyle> m_StrokeStyle; // ¹Ì±¸Çö
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_FillBrush;
	float m_LineStroke;
	bool IsFill;
	bool IsRound;
public:
	CRectangle();
	~CRectangle();

	bool Initialize(Direct2DEngine* pD2DEngine, int x, int y, int width, int height);
	bool Draw();
	bool DrawDirect(float x, float y);
	bool Update();
	void Release();

	void SetFill(bool isFill);
	void SetRound(bool isRound);
	void SetStroke(float stroke);
	void SetFillColor(D2D1::ColorF color);

	void SetPosX(float x);
	void SetPosY(float y);
	void SetPos(float x, float y);
	void SetWidth(float width);
	void SetHeight(float height);
};

