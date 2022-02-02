#pragma once
#include "../BasicUI/CBitmap.h"
#include "../BasicUI/Shape.h"
#include "../BasicUI/UIBoxArea.h"
#include "../BasicUI/Text.h"
#include "../AdvancedUI/Button.h"
#include <string>

#define MAX_INPUT_TEXT_SIZE 128

class TextInputField
{
protected:
	UIBoxArea m_Area;
	std::wstring m_InputText;
	Text* m_OutputText;
	Shape* m_BackGroundShape;
	CBitmap* m_BackGroundImage;

	bool m_DeleteAllStringAfterEnter; // 엔터를 쳤을 때, 내용을 지울 것인지, 아닐 것 인지 결정
	bool m_IsFocus;

	Direct2DEngine* extEngine;
public:
	TextInputField();
	TextInputField(const TextInputField& other);
	virtual ~TextInputField();

	virtual bool Initialize(Direct2DEngine* D2DEngine, int x, int y, int width, int height);
	virtual bool Render();
	virtual bool Update();
	virtual bool Release();

	virtual void CreateBitmap(const WCHAR* bitmap);
	virtual CBitmap* GetBitmap();
	virtual void CreateShape(int shape);
	virtual Shape* GetShape();

	virtual bool IsInside(int x, int y);
	virtual bool GetFocus();

	virtual void Normally(); // 평상시
	virtual void Pressed(); // 누를시
	virtual void Touched(); // 마우스가 필드 위에 존재할 때
	virtual void Selected(); // 필드 선택시
	virtual void Disabled(); // 필드 비선택시

	virtual void SetInputText(WCHAR* string);
	virtual std::wstring GetInputText();
	virtual Text* GetOutputText();

	virtual LRESULT TextInputFieldFunc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

