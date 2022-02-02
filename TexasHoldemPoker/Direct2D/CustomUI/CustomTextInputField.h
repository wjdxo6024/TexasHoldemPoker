#pragma once
#include "../AdvancedUI/TextInputField.h"
class CustomTextInputField :
	public TextInputField
{
private:
	unsigned int m_MaxStringSize = MAX_INPUT_TEXT_SIZE;
public:
	bool Initialize(Direct2DEngine* D2DEngine, int x, int y, int width, int height);

	void Normally(); // ����
	void Pressed(); // ������
	void Touched(); // ���콺�� �ʵ� ���� ������ ��
	void Selected(); // �ʵ� ���ý�
	void Disabled(); // �ʵ� ���ý�

	void SetMaxStringSize(unsigned int max_size);

	LRESULT TextInputFieldFunc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

