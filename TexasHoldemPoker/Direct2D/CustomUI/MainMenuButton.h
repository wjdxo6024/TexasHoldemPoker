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
	virtual void Normally(); // ����
	virtual void Pressed(); // ������
	virtual void Touched(); // ���콺�� ��ư ���� ������ ��
	virtual void Selected(); // ��ư ���ý�
	virtual void Disabled(); // ��ư ���ý�
};

