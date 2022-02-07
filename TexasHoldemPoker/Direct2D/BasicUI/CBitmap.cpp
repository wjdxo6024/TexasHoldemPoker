#include "CBitmap.h"

bool CBitmap::Initialize(Direct2DEngine* pD2DEngine, int x, int y, int width, int height, WCHAR* filePath)
{
	m_pD2DEngine = pD2DEngine;
	m_imageX = x;
	m_imageY = y;
	m_Width = width;
	m_Height = height;
	m_filePath = filePath;
	// 여러 포맷을 받아서 변환 후 하나의 비트맵으로 생성
	Microsoft::WRL::ComPtr<IWICBitmapDecoder> decoder;
	Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> source;
	Microsoft::WRL::ComPtr<IWICFormatConverter> converter;
	Microsoft::WRL::ComPtr<IWICStream> stream;
	Microsoft::WRL::ComPtr<IWICBitmapScaler> scaler;

	// factory 생성
	CoInitialize(NULL);
	if (FAILED(CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&factory))))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Create Factory", L"Bitmap Error", MB_OK);
#endif
		return false;
	}
	
	if (FAILED(factory->CreateDecoderFromFilename(m_filePath.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad,
		decoder.GetAddressOf())))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Create Decoder", L"Bitmap Error", MB_OK);
#endif
		return false;
	}

	if (FAILED(decoder->GetFrame(0, &source))) // 프레임을 저장
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Get Frame.", L"Bitmap Error", MB_OK);
#endif
		return false;
	}

	if (FAILED(factory->CreateFormatConverter(converter.GetAddressOf())))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Create Converter.", L"Bitmap Error", MB_OK);
#endif
		return false;
	}

	if (FAILED(converter->Initialize(*source.GetAddressOf(), GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeMedianCut)))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Initialize Source.", L"Bitmap Error", MB_OK);
#endif
		return false;
	}

	// 비트맵 생성
	if (FAILED(m_pD2DEngine->GetDeviceContext()->CreateBitmapFromWicBitmap(*converter.GetAddressOf(), NULL, &m_Bitmap)))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Create Bitmap.", L"Bitmap Error", MB_OK);
#endif
		return false;
	}

	return true;
}

bool CBitmap::InitializeWithDataOnTheInside()
{
	return this->Initialize(m_pD2DEngine, m_imageX, m_imageY, m_Width, m_Height, const_cast<WCHAR*>(m_filePath.data()));
}


bool CBitmap::Draw()
{
	m_pD2DEngine->GetDeviceContext()->SetTransform(D2D1::IdentityMatrix());
	D2D1_RECT_F rect = { m_imageX, m_imageY, m_imageX + m_Width, m_imageY + m_Height};
	m_pD2DEngine->GetDeviceContext()->DrawBitmap(m_Bitmap, rect);
	return true;
}

bool CBitmap::DrawDirect(int x, int y, int width, int height)
{
	m_pD2DEngine->GetDeviceContext()->SetTransform(D2D1::IdentityMatrix());
	D2D1_RECT_F rect = { x, y, x + width, y + height };
	m_pD2DEngine->GetDeviceContext()->DrawBitmap(m_Bitmap, rect);
	return true;
}

bool CBitmap::Update()
{
	return true;
}

bool CBitmap::Release()
{
	SAFE_RELEASE(m_Bitmap);
	SAFE_RELEASE(factory);

	return true;
}

bool CBitmap::Repos(float x, float y)
{
	m_imageX = x;
	m_imageY = y;
	return true;
}

bool CBitmap::OnResize(Direct2DEngine* engine, int width, int height)
{
	m_pD2DEngine = engine;
	m_Width = width;
	m_Height = height;
	this->Release();
	this->InitializeWithDataOnTheInside();
	return true;
}