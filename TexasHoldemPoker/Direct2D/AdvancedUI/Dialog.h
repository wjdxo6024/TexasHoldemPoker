#pragma once
#include "../BasicUI/Text.h"
#include "../BasicUI/Shape.h"
#include "../BasicUI/CBitmap.h"
#include "../AdvancedUI/Button.h"
#include "../../GameEvent/ButtonEvents.h"
#include <vector>

// 기본 Dialog는 Yes, No, Confirm, Cancel중 하나 이상을 포함한 기본 메세지 박스이다.

class Dialog
{
protected:
	Text* m_NoticeText;
	Text* m_ContentText;

	Direct2DEngine* extEngine;
	Shape* m_TitleShape;
	Shape* m_ContentShape;

	CBitmap* m_BackGroundImage;

	std::vector<Button*> m_Buttons;
public:
	Dialog();
	Dialog(const Dialog& other);
	virtual ~Dialog();

	virtual bool Initialize(Direct2DEngine* D2DEngine, int x, int y, int width, int height);
	virtual bool Render();
	virtual bool Update();
	virtual bool Release();

	virtual void SetNoticeText(const WCHAR* Text);
	virtual void SetContentText(const WCHAR* Text);
	virtual void CreateBitmap(const WCHAR* bitmap);
	virtual void CreateShape(int shape);
	virtual void CreateButton(const WCHAR* Text, ButtonEvent Event);

	virtual Button* GetButton(int index);
	virtual std::vector<Button*>& GetButtons();
};

