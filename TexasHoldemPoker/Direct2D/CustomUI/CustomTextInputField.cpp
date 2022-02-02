#include "CustomTextInputField.h"

bool CustomTextInputField::Initialize(Direct2DEngine* D2DEngine, int x, int y, int width, int height)
{
	TextInputField::Initialize(D2DEngine, x, y, width, height);

	this->CreateShape(_SHAPE_RECTANGLE);
	reinterpret_cast<CRectangle*>(this->GetShape())->SetFill(false);
	this->GetOutputText()->SetFontSize(this->GetOutputText()->GetFontSize() * 1.5);
	this->GetOutputText()->SetTextWidthAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
	this->GetOutputText()->SetTextHeightAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	m_MaxStringSize = 10;

	return true;
}

void CustomTextInputField::Normally()
{
	if (!m_IsFocus)
	{
		reinterpret_cast<CRectangle*>(this->GetShape())->SetFill(false);
		reinterpret_cast<CRectangle*>(this->GetShape())->SetColor(D2D1::ColorF::Aqua);
		this->GetOutputText()->SetFontColor(D2D1::ColorF::White);
	}
}

void CustomTextInputField::Pressed()
{

}

void CustomTextInputField::Touched()
{
	
}

void CustomTextInputField::Selected()
{
	if (m_IsFocus)
	{
		reinterpret_cast<CRectangle*>(this->GetShape())->SetFill(true);
		reinterpret_cast<CRectangle*>(this->GetShape())->SetColor(D2D1::ColorF::Red);
		reinterpret_cast<CRectangle*>(this->GetShape())->SetFillColor(D2D1::ColorF::White);
		this->GetOutputText()->SetFontColor(D2D1::ColorF::Black);
	}
}

void CustomTextInputField::Disabled()
{

}

void CustomTextInputField::SetMaxStringSize(unsigned int max_size)
{
	m_MaxStringSize = max_size;
}

LRESULT CustomTextInputField::TextInputFieldFunc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_IsFocus)
	{
		switch (message)
		{
		case WM_CHAR:
		{
			switch (wParam)
			{
			case VK_RETURN:
				break;
			case VK_BACK:
				if (m_InputText.size() > 0)
					m_InputText.pop_back();
				break;
			default:
				if (m_InputText.size() < m_MaxStringSize)
					m_InputText += (WCHAR)wParam;
			}

			// 업데이트
			m_OutputText->SetText(const_cast<WCHAR*>(m_InputText.data()));
		}
		}
	}

	return 0;
}