#ifndef _TEXT_H_
#define _TEXT_H_

#include "../Direct2DEngine.h"
#include <memory>
#include <wrl/client.h>
#include <string>

class Text
{
private:
	Microsoft::WRL::ComPtr<IDWriteTextFormat> m_textFormat;
	Microsoft::WRL::ComPtr<IDWriteTextLayout> m_textLayout;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_TextBrush;

	std::wstring m_TextContents;

	// Text State
	float m_FontSize;
	int m_IsBold;
	DWRITE_FONT_STYLE m_Style;
	DWRITE_FONT_WEIGHT m_Weight;
	DWRITE_FONT_STRETCH m_Stretch;
	DWRITE_TEXT_ALIGNMENT m_WidthAlign;
	DWRITE_PARAGRAPH_ALIGNMENT m_HeightAlign;
	
	Direct2DEngine* m_pD2DEngine;

public:
	Text();
	Text(const Text& other);
	virtual ~Text();

	bool Initialize(Direct2DEngine* D2DEngine, WCHAR* String);
	bool Draw(float x, float y);
	bool DrawDirect(float x, float y);
	bool DrawDirectInRect(RECT rt);
	bool DrawDirectWithString(float x, float y, WCHAR* String);
	bool Update();
	void Release();

	void SetFontStyle(DWRITE_FONT_STYLE font);
	void SetFontEffect(const char* fonteffect);

	void SetFontWeight(DWRITE_FONT_WEIGHT weight);
	void SetFontBold(bool isBold);

	void SetFontSize(float fontSize);
	float GetFontSize();

	void SetFontColor(D2D1::ColorF color);
	D2D1_COLOR_F GetFontColor();

	void SetTextWidthAlign(DWRITE_TEXT_ALIGNMENT textAlign);
	void SetTextHeightAlign(DWRITE_PARAGRAPH_ALIGNMENT textAlign);
	void SetPosition(float, float);
	void SetText(WCHAR* string);
};

#endif