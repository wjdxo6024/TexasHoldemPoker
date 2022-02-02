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
	void InitializeUsingPoint(int startX, int startY, int endX, int endY); // 시작 점에서 끝 점을 가로지르는 경우(반드시 좌에서 우로)
	bool IsInside(int x, int y) override;

	RectTransform* GetTransform(); // 변경 후 반드시 AreaUpdate()할 것, 혹은 GetRect로 영역 불러 올 것.
	RECT GetRect();
};

