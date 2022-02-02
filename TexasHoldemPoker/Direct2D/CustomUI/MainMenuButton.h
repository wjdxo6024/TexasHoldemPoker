#pragma once
#include "../AdvancedUI/Button.h"
class MainMenuButton :
	public Button
{
private:

public:
	MainMenuButton();
	MainMenuButton(const MainMenuButton& other);
	virtual ~MainMenuButton();

	virtual bool InitializeEx(Direct2DEngine* D2DEngine, int x, int y, int width, int height, WCHAR* text);

	// Button State
	virtual void Normally(); // 평상시
	virtual void Pressed(); // 누를시
	virtual void Touched(); // 마우스가 버튼 위에 존재할 때
	virtual void Selected(); // 버튼 선택시
	virtual void Disabled(); // 버튼 비선택시
};

