#pragma once
#include "UIArea.h"
#include "RectTransform.h"
#include "CRectangle.h"
#include "../../Funtions/MyFunctions.h"
#include <Windows.h>

class UIBoxArea : public UIArea
{
private:
	RECT m_BoxArea;
	RectTransform m_RectTransform;

	CRectangle TestRect;
public:
	UIBoxArea();
	UIBoxArea(const UIBoxArea& other);
	virtual ~UIBoxArea();

	void AreaUpdate();
	void AreaResize(int WindowWidth, int WindowHeight);
	void Initialize(int left, int right, int top, int bottom);
	void Initialize(RECT rect);
	void InitializeA(int x, int y, int width, int height);
	void InitializeUsingPoint(int startX, int startY, int endX, int endY); // ���� ������ �� ���� ���������� ���(�ݵ�� �¿��� ���)
	bool IsInside(int x, int y) override;

	RectTransform* GetTransform(); // ���� �� �ݵ�� AreaUpdate()�� ��, Ȥ�� GetRect�� ���� �ҷ� �� ��.
	RECT GetRect();
};

