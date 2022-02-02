#pragma once
#include "../AdvancedUI/TextInputField.h"
class CustomTextInputField :
	public TextInputField
{
private:
	unsigned int m_MaxStringSize = MAX_INPUT_TEXT_SIZE;
public:
	bool Initialize(Direct2DEngine* D2DEngine, int x, int y, int width, int height);

	void Normally(); // 평상시
	void Pressed(); // 누를시
	void Touched(); // 마우스가 필드 위에 존재할 때
	void Selected(); // 필드 선택시
	void Disabled(); // 필드 비선택시

	void SetMaxStringSize(unsigned int max_size);

	LRESULT TextInputFieldFunc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

