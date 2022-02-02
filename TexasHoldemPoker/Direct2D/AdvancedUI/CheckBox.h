#pragma once
#include "../BasicUI/CRectangle.h"
#include "../BasicUI/UIBoxArea.h"
#include "../../Funtions/MyFunctions.h"

class CheckBox
{
private:
	bool m_IsCheck;
	CRectangle* m_BackGround;
	CRectangle* m_CheckRectangle;
	UIBoxArea m_Area;

	Direct2DEngine* extEngine;

	D2D1::ColorF m_NormalColor = D2D1::ColorF::Black;
	D2D1::ColorF m_PressColor = D2D1::ColorF::Black;
	D2D1::ColorF m_TouchColor = D2D1::ColorF::Black;
	D2D1::ColorF m_SelectColor = D2D1::ColorF::Black;
	D2D1::ColorF m_DisabledColor = D2D1::ColorF::Black;

public:
	CheckBox();
	CheckBox(const CheckBox& other);
	virtual ~CheckBox();

	virtual bool Initialize(Direct2DEngine* D2DEngine, int x, int y, int width, int height);
	virtual bool Render();
	virtual bool Update();
	virtual bool Release();
	virtual bool AreaResize(int width, int height);

	virtual bool IsInside(int x, int y);
	virtual void Check();
	virtual bool GetCheck();
	virtual void SetCheck(bool check);

	virtual void Normally(); // ����
	virtual void Pressed(); // ������
	virtual void Touched(); // ���콺�� ��ư ���� ������ ��
	virtual void Selected(); // ��ư ���ý�
	virtual void Disabled(); // ��ư ���ý�
};

