#pragma once
#include "../AdvancedUI/TextInputField.h"

#define MAX_INPUT_DIGIT 9 // integer는 2,147,483,647

class NumberInputField : public TextInputField
{
private:
	int m_InputNumber;
	int m_MaxDigit = MAX_INPUT_DIGIT;
public:
	bool Initialize(Direct2DEngine* D2DEngine, int x, int y, int width, int height);

	void Normally(); // 평상시
	void Pressed(); // 누를시
	void Touched(); // 마우스가 필드 위에 존재할 때
	void Selected(); // 필드 선택시
	void Disabled(); // 필드 비선택시

	LRESULT TextInputFieldFunc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void SetMaxDigit(unsigned int digit);
	int GetNumber();
};

