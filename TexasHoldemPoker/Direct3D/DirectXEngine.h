#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "../GameOption/GameOption.h"
using namespace DirectX;

class DirectXEngine
{
private:
	bool m_vsync_enabled = false;
	int m_videoCardMemory = 0;
	char m_videoCardDescription[128] = { 0, };
	D3D_FEATURE_LEVEL m_featureLevel;
	IDXGISwapChain* m_swapChain = nullptr;
	ID3D11Device* m_device = nullptr;
	ID3D11DeviceContext* m_deviceContext = nullptr;
	ID3D11RenderTargetView* m_renderTargetView = nullptr;
	ID3D11Texture2D* m_depthStencilBuffer = nullptr;
	ID3D11DepthStencilState* m_depthStencilState = nullptr;
	ID3D11DepthStencilView* m_depthStencilView = nullptr;
	ID3D11RasterizerState* m_rasterState = nullptr;

	XMMATRIX m_projectionMatrix;
	XMMATRIX m_worldMatrix;
	XMMATRIX m_orthoMatrix;

	int screenWidth;
	int screenHeight;

	float screenDepth = 1000.0f;
	float screenNear = 0.1f;

	// RTT --------------------------------------
	ID3D11DepthStencilState* m_depthDisabledStencilState = nullptr;
	ID3D11BlendState* m_alphaEnableBlendingState = nullptr;
	ID3D11BlendState* m_alphaDisableBlendingState = nullptr;
public:
	DirectXEngine();
	DirectXEngine(int, int);
	DirectXEngine(const DirectXEngine&);
	~DirectXEngine();

	bool Initialize(int Width, int Height, HWND hWnd, bool fullscreen);
	void Release();
	bool Frame();
	bool Render();

	void BeginScene();
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();
	IDXGISwapChain* GetSwapChain();
	void GetProjectionMatrix(XMMATRIX&);
	void GetWorldMatrix(XMMATRIX&);
	void GetOrthoMatrix(XMMATRIX&);

	void GetVideoCardInfo(char* cardName, int& memory);

	float GetScreenDepth();
	float GetScreenNear();

	int GetHeight();
	int GetWidth();

	void OnResize(int width, int height);
	bool OnResize(HWND hWnd, GameOption* gameOption);

	void TurnZBufferOn();
	void TurnZBufferOff();

	// RTT ------------------------------------
	bool CreateStecilBufferForRTT();

	void TurnOnAlphaBlending();
	void TurnOffAlphaBlending();

	ID3D11DepthStencilView* GetDepthStencilView();
	void SetBackBufferRenderTarget();
};

