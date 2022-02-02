#pragma once
#ifndef _D2DENGINE_H_
#define _D2DENGINE_H_
#include "../Direct3D/DirectXEngine.h"
#include "../GameOption/GameOption.h"
#include <d2d1effects.h>
#include <d2d1effecthelpers.h>
#include <d2d1_3.h>
#include <d2d1_3helper.h>
#include <d2d1_2.h>
#include <d2d1_2helper.h>
#include <d2d1_1.h>
#include <d2d1_1helper.h>
#include <dwrite.h>
#include <wrl/client.h>
#include <WinUser.h>
#include <ShellScalingApi.h>

class Direct2DEngine
{
private:
	// Direct2D
	IDXGIDevice* m_dxgiDevice;
	ID2D1Device* m_d2dDevice;
	ID2D1DeviceContext* m_d2dDeviceContext;
	IDWriteFactory* m_writeFactory;

	//ID2D1Factory1* factory = nullptr;
	//IDXGISurface* dxgiBuffer = nullptr;
	//ID2D1Bitmap1* targetBitmap = nullptr;

	GameOption* extGameOption;
	DirectXEngine* extD3DEngine;
	// Text
	ID2D1SolidColorBrush* yellowBrush;
	ID2D1SolidColorBrush* blackBrush;
	ID2D1SolidColorBrush* whiteBrush;

	IDWriteTextFormat* m_textFormatFPS;
	IDWriteTextFormat* m_normalFormatText;
	IDWriteTextFormat* m_highlightFormatText;

	IDWriteTextLayout* m_textLayoutFPS;

private:
	void onResize();
	bool initTextRender();
	bool setTextRender();
	void TextQuit();
public:
	Direct2DEngine();
	Direct2DEngine(const Direct2DEngine& other);
	~Direct2DEngine();

	bool Initialize(DirectXEngine* DXEngine, HWND hWnd, GameOption* option, bool fullscreen);

	bool BeginDraw();
	bool EndDraw();

	bool Render();
	bool Update();
	bool Release();

	void SetBrush(WCHAR*);
	IDWriteFactory* GetWriteFactory();
	ID2D1DeviceContext* GetDeviceContext();
	ID2D1Device* GetDevice();

	int GetScreenWidth();
	int GetScreenHeight();

	DirectXEngine* GetD3DEngine();

	bool OnResize(HWND hWnd, GameOption* gameOption);
};


#endif