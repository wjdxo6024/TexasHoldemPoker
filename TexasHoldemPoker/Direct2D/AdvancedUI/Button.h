#pragma once
#include "../BasicUI/RectTransform.h"
#include "../../GameEvent/ButtonEvents.h"
#include "../BasicUI/UIBoxArea.h"
#include "../BasicUI/UIBoxArea.h"
#include "../BasicUI/Text.h"
#include "../BasicUI/CBitmap.h"
#include "../BasicUI/Shape.h"
#include "../BasicUI/CRectangle.h"
#include "../BasicUI/CEllipse.h"
#include "../../Funtions/MyFunctions.h"
// ��ư�� �⺻ ���� ����(�̺�Ʈ ó��)���� ���
// �̹��� ��ư�̳� ���� ��ư Ȥ�� ȥ�� ��ư�� �ڽ� Ŭ�������� ó��

#define NORMALCOLOR 0
#define PRESSCOLOR 1
#define TOUCHCOLOR 2
#define SELECTCOLOR 3
#define DISABLEDCOLOR 4

class Button
{
protected:
	UIBoxArea m_Area;
	Text* m_Text;
	CBitmap* m_Bitmap;
	Shape* m_Shape;
	Direct2DEngine* extD2DEngine;

	// Button Event Color
	D2D1::ColorF m_NormalColor = D2D1::ColorF::Black;
	D2D1::ColorF m_PressColor = D2D1::ColorF::Black;
	D2D1::ColorF m_TouchColor = D2D1::ColorF::Black;
	D2D1::ColorF m_SelectColor = D2D1::ColorF::Black;
	D2D1::ColorF m_DisabledColor = D2D1::ColorF::Black;

	ButtonEvent m_ButtonEvent;
public:
	Button();
	Button(const Button& other);
	virtual ~Button();

	virtual bool Initialize(Direct2DEngine* D2DEngine, int x, int y, int width, int height);
	virtual bool Update();
	virtual bool Render();
	virtual bool Release();

	virtual bool AreaResize(int width, int height);

	virtual void SetWidth(int width);
	virtual int GetWidth();
	virtual void SetHeight(int height);
	virtual int GetHeight();

	virtual void CreateText(const WCHAR* text);
	virtual void CreateBitmap(const WCHAR* bitmap);
	virtual void CreateShape(int shape);

	virtual Text* GetText();
	virtual CBitmap* GetBitmap();
	virtual Shape* GetShape();

	virtual void SetEvent(ButtonEvent Event);
	virtual ButtonEvent GetEvent();
	virtual void OnClick();
	virtual bool IsInside(int x, int y);

	// Button State
	virtual void Normally(); // ����
	virtual void Pressed(); // ������
	virtual void Touched(); // ���콺�� ��ư ���� ������ ��
	virtual void Selected(); // ��ư ���ý�
	virtual void Disabled(); // ��ư ���ý�
};

