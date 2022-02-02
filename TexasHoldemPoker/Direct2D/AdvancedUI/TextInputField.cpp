#include "TextInputField.h"

TextInputField::TextInputField()
{
	m_DeleteAllStringAfterEnter = false;
	m_IsFocus = false;
}

TextInputField::TextInputField(const TextInputField& other)
{

}

TextInputField::~TextInputField()
{

}

bool TextInputField::Initialize(Direct2DEngine* D2DEngine, int x, int y, int width, int height)
{
	extEngine = D2DEngine;
	m_Area.InitializeA(x, y, width, height);

	m_OutputText = new Text;
	if (m_OutputText != NULL)
	{
		m_OutputText->Initialize(extEngine, const_cast<WCHAR*>(L""));
	}
	else
		return false;

	return true;
}

bool TextInputField::Render()
{
	if (m_BackGroundImage != NULL)
		m_BackGroundImage->Draw();

	if (m_BackGroundShape != NULL)
		m_BackGroundShape->Draw();

	m_OutputText->DrawDirectInRect(m_Area.GetRect());
	return true;
}

bool TextInputField::Update()
{
	return true;
}

bool TextInputField::Release()
{
	SAFE_RELEASE_AND_DELETE(m_BackGroundImage);
	SAFE_RELEASE_AND_DELETE(m_BackGroundShape);
	SAFE_RELEASE_AND_DELETE(m_OutputText);
	return true;
}

void TextInputField::CreateBitmap(const WCHAR* bitmap)
{
	m_BackGroundImage = new CBitmap;
	if (m_BackGroundImage == NULL)
		return;

	if (!m_BackGroundImage->Initialize(extEngine, m_Area.GetTransform()->GetPosX(), m_Area.GetTransform()->GetPosY(),
		m_Area.GetTransform()->GetWidth(), m_Area.GetTransform()->GetHeight(), const_cast<WCHAR*>(bitmap)))
	{
		m_BackGroundImage->Release();
		delete m_BackGroundImage;
		m_BackGroundImage = NULL;
	}
}

CBitmap* TextInputField::GetBitmap()
{
	return m_BackGroundImage;
}

void TextInputField::CreateShape(int shape)
{
	SAFE_RELEASE_AND_DELETE(m_BackGroundShape);

	if (shape == _SHAPE_BASIC)
		m_BackGroundShape = new Shape();
	else if (shape == _SHAPE_RECTANGLE)
		m_BackGroundShape = new CRectangle();
	else if (shape == _SHAPE_ELLIPSE)
		m_BackGroundShape = new CEllipse();

	m_BackGroundShape->Initialize(extEngine, m_Area.GetTransform()->GetPosX(), m_Area.GetTransform()->GetPosY(),
		m_Area.GetTransform()->GetWidth(), m_Area.GetTransform()->GetHeight());
	return;
}

Shape* TextInputField::GetShape()
{
	return m_BackGroundShape;
}

bool TextInputField::IsInside(int x, int y)
{
	if (m_Area.IsInside(x, y))
	{
		m_IsFocus = true;
		return true;
	}
	else
	{
		m_IsFocus = false;
		return false;
	}
}

bool TextInputField::GetFocus()
{
	return m_IsFocus;
}

void TextInputField::Normally()
{

}

void TextInputField::Pressed()
{

}

void TextInputField::Touched()
{

}

void TextInputField::Selected()
{

}

void TextInputField::Disabled()
{

}

void TextInputField::SetInputText(WCHAR* string)
{

}

std::wstring TextInputField::GetInputText()
{
	if (m_DeleteAllStringAfterEnter)
	{
		std::wstring TempText = m_InputText;
		m_InputText.clear();
		return TempText;
	}
	else
		return m_InputText;
}

Text* TextInputField::GetOutputText()
{
	return m_OutputText;
}

LRESULT TextInputField::TextInputFieldFunc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
					if (m_InputText.size() < MAX_INPUT_TEXT_SIZE)
						m_InputText += (WCHAR)wParam;
				}

				// 업데이트
				m_OutputText->SetText(const_cast<WCHAR*>(m_InputText.data()));
			}
		}
	}

	return 0;
}