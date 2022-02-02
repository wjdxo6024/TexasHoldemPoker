#include "CardImages.h"

bool CardImages::Initialize(Direct2DEngine* pD2DEngine, GameOption* gameOption, WCHAR* filePath)
{
	extGameOption = gameOption;
	CBitmap::Initialize(pD2DEngine, 0, 0, extGameOption->GetWidth(), extGameOption->GetHeight(), filePath);
	m_CardWidth = m_Bitmap->GetSize().width / 13;
	m_CardHeight = m_Bitmap->GetSize().height / 5;
	
	return true;
}

bool CardImages::Draw(int x, int y)	// Draw Back Card
{
	D2D1_RECT_F sourceRT = { m_CardWidth * 2, m_CardHeight * 4, m_CardWidth * 3, m_CardHeight * 5};
	D2D1_RECT_F destinationRT = { ScalingUI_X(x, extGameOption->GetWidth()), ScalingUI_Y(y, extGameOption->GetHeight())
		, ScalingUI_X(x + m_CardWidth, extGameOption->GetWidth()), ScalingUI_Y(y + m_CardHeight, extGameOption->GetHeight()) };
	m_pD2DEngine->GetDeviceContext()->DrawBitmap(m_Bitmap, destinationRT, 1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		sourceRT);

	return true;
}

bool CardImages::Draw(int x, int y, Card& card) // Draw Card
{
	D2D1_RECT_F sourceRT = { m_CardWidth * (card.number - 1),
		m_CardHeight * (card.shape - 1),
		m_CardWidth + (m_CardWidth * (card.number - 1)),
		m_CardHeight + (m_CardHeight * (card.shape - 1))};
	D2D1_RECT_F destinationRT = { ScalingUI_X(x, extGameOption->GetWidth()),
		ScalingUI_Y(y, extGameOption->GetHeight()),
		ScalingUI_X(x + m_CardWidth, extGameOption->GetWidth()),
		ScalingUI_Y(y + m_CardHeight, extGameOption->GetHeight()) };
	m_pD2DEngine->GetDeviceContext()->DrawBitmap(
		m_Bitmap,
		destinationRT,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		sourceRT);

	return true;
}

bool CardImages::Update()
{
	return true;
}

bool CardImages::Update(double deltaTime)
{
	return true;
}

bool CardImages::Release()
{
	CBitmap::Release();
	return true;
}


float CardImages::GetCardWidth()
{
	return m_CardWidth;
}

float CardImages::GetCardHeight()
{
	return m_CardHeight;
}