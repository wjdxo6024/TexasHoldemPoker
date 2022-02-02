#pragma once
#include "../BasicUI/CBitmap.h"
#include "../BasicUI/CRectangle.h"
#include "../BasicUI/UIBoxArea.h"
#include "../BasicUI/Text.h"
#include "../../Funtions/MyFunctions.h"
// TextOuputField란 텍스트를 출력하기 위한 여러 공간으로써
// RectTransform과 결합하여 특정 공간에 텍스트를 출력하는 것이다. ex) 캐릭터 대화 창 등..

class TextOutputField
{
protected:
	UIBoxArea m_Area;
	CBitmap* m_BackgroundImage;
	CRectangle* m_BackgroundRect;

	Text* m_Text;
	int m_TextIntervalWidth;
	int m_TextIntervalHeight;
	std::wstring m_TextContent;
	Direct2DEngine* extEngine;

public:
	TextOutputField();
	TextOutputField(const TextOutputField& other);
	virtual ~TextOutputField();

	virtual bool Initialize(Direct2DEngine* D2DEngine, int x, int y, int width, int height);
	virtual bool Render();
	virtual bool Update();
	virtual bool Release();

	bool CreateImage(WCHAR* filepath);
	CBitmap* GetImage();
	bool CreateRectangle();
	CRectangle* GetRect();

	void SetTextInterval(int width, int height);
	void SetTextIntervalWidth(int width);
	void SetTextIntervalHeight(int height);

	void SetTextContent(WCHAR* string);
	Text* GetText();
};

