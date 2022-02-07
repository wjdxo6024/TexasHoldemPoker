#ifndef _CBITMAP_H_
#define _CBITMAP_H_
#include "../Direct2DEngine.h"
#include "../../Funtions/MyFunctions.h"
#include "RectTransform.h"
#include <memory>
#include <wrl/client.h>
#include <wincodec.h>

class CBitmap
{
protected:
	ID2D1Bitmap* m_Bitmap;
	IWICImagingFactory* factory;

	float m_imageX, m_imageY;
	float m_Width, m_Height;

	D2D1_POINT_2F m_CenterPos;
	D2D1_SIZE_F m_RenderSize;
	float m_RotationDegree;
	std::wstring m_filePath;

	Direct2DEngine* m_pD2DEngine = NULL;
public:
	virtual bool InitializeWithDataOnTheInside();
	virtual bool Initialize(Direct2DEngine* pD2DEngine, int x, int y, int width, int height, WCHAR* filePath);
	virtual bool Draw();
	virtual bool DrawDirect(int x, int y, int width, int height);
	virtual bool Update();
	virtual bool Release();

	virtual bool Repos(float x, float y);
	virtual bool OnResize(Direct2DEngine* engine, int width, int height);
};

#endif