#include "NumberInputField.h"

bool NumberInputField::Initialize(Direct2DEngine* D2DEngine, int x, int y, int width, int height)
{
	TextInputField::Initialize(D2DEngine, x, y, width, height);

	this->CreateShape(_SHAPE_RECTANGLE);
	reinterpret_cast<CRectangle*>(this->GetShape())->SetFill(false);
	this->GetOutputText()->SetFontSize(this->GetOutputText()->GetFontSize() * 1.5);
	this->GetOutputText()->SetTextWidthAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
	this->GetOutputText()->SetTextHeightAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	return true;
}

void NumberInputField::Normally()
{
	if (!m_IsFocus)
	{
		reinterpret_cast<CRectangle*>(this->GetShape())->SetFill(false);
		reinterpret_cast<CRectangle*>(this->GetShape())->SetColor(D2D1::ColorF::Aqua);
		this->GetOutputText()->SetFontColor(D2D1::ColorF::White);
	}
}

void NumberInputField::Pressed()
{

}

void NumberInputField::Touched()
{

}

void NumberInputField::Selected()
{
	if (m_IsFocus)
	{
		reinterpret_cast<CRectangle*>(this->GetShape())->SetFill(true);
		reinterpret_cast<CRectangle*>(this->GetShape())->SetColor(D2D1::ColorF::Red);
		reinterpret_cast<CRectangle*>(this->GetShape())->SetFillColor(D2D1::ColorF::White);
		this->GetOutputText()->SetFontColor(D2D1::ColorF::Black);
	}
}

void NumberInputField::Disabled()
{

}

LRESULT NumberInputField::TextInputFieldFunc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_IsFocus)
	{
		switch (message)
		{
		case WM_CHAR:
		{
			switch (wParam)
			{
				// 0 ~ 9
			case 0x30:
				if (m_InputText[0] == L'0')
					break;
			case 0x31:
			case 0x32:
			case 0x33:
			case 0x34:
			case 0x35:
			case 0x36:
			case 0x37:
			case 0x38:
			case 0x39:
				if (m_InputText.size() < m_MaxDigit)
				{
					m_InputText += (WCHAR)wParam;
					m_InputNumber = _wtoi(m_InputText.c_str());
					_itow(m_InputNumber, &m_InputText[0], 10);
				}
				break;
			case VK_BACK:
				if (m_InputText.size() > 0)
					m_InputText.pop_back();
				break;
			}

			// 업데이트
			m_OutputText->SetText(const_cast<WCHAR*>(m_InputText.data()));
		}
		}
	}

	return 0;
}

void NumberInputField::SetMaxDigit(unsigned int digit)
{
	m_MaxDigit = digit;
}

int NumberInputField::GetNumber()
{
	return m_InputNumber;
}