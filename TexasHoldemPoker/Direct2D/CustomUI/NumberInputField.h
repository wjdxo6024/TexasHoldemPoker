#pragma once
#include "../AdvancedUI/TextInputField.h"

#define MAX_INPUT_DIGIT 9 // integer�� 2,147,483,647

class NumberInputField : public TextInputField
{
private:
	int m_InputNumber;
	int m_MaxDigit = MAX_INPUT_DIGIT;
public:
	bool Initialize(Direct2DEngine* D2DEngine, int x, int y, int width, int height);

	void Normally(); // ����
	void Pressed(); // ������
	void Touched(); // ���콺�� �ʵ� ���� ������ ��
	void Selected(); // �ʵ� ���ý�
	void Disabled(); // �ʵ� ���ý�

	LRESULT TextInputFieldFunc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void SetMaxDigit(unsigned int digit);
	int GetNumber();
};

