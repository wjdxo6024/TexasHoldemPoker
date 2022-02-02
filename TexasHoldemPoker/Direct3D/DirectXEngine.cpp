#include "DirectXEngine.h"

DirectXEngine::DirectXEngine()
{

}

DirectXEngine::DirectXEngine(int width, int height)
{
	screenWidth = width;
	screenHeight = height;
}

DirectXEngine::DirectXEngine(const DirectXEngine& dxEngine)
{

}

DirectXEngine::~DirectXEngine()
{
	this->Release();
}

bool DirectXEngine::Initialize(int Width, int Height, HWND hWnd, bool fullscreen)
{
	screenWidth = Width;
	screenHeight = Height;

	// ��������ȭ ���� TRUE
	m_vsync_enabled = true;

	//�׷��� �������̽� ���丮
	IDXGIFactory* factory = nullptr;
	if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory)))
	{
		MessageBox(NULL, L"Cannot Crate  DXGIFactory.", L"Error", MB_OK);
		return false;
	}

	IDXGIAdapter* adapter = nullptr;
	if (FAILED(factory->EnumAdapters(0, &adapter)))
	{
		MessageBox(NULL, L"Cannot Crate Adapter.", L"Error", MB_OK);
		return false;
	}

	// ��¿� ���� ù��° ���
	IDXGIOutput* adapterOutput = nullptr;
	if (FAILED(adapter->EnumOutputs(0, &adapterOutput)))
	{
		MessageBox(NULL, L"Cannot Crate outputAdapter.", L"Error", MB_OK);
		return false;
	}

	// ��¿� ���� ǥ�� ���Ŀ� �´� ��� ����
	unsigned int numModes = 0;
	if (FAILED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL)))
	{
		MessageBox(NULL, L"Cannot Get DisplayModeList.", L"Error", MB_OK);
		return false;
	}

	// ������ ��� ����Ϳ� �׷���ī�� ������ ������ ����Ʈ ����
	DXGI_MODE_DESC* displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList)
	{
		MessageBox(NULL, L"Cannot Crate ModeList.", L"Error", MB_OK);
		return false;
	}

	//���÷��� ��忡 ���� ����Ʈ ä��
	if (FAILED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList)))
	{
		MessageBox(NULL, L"Cannot Fill ModeList.", L"Error", MB_OK);
		return false;
	}

	// ȭ�� �ʺ�/���� �� �´� ���÷��� ��� ��ġ
	unsigned int numerator = 0;
	unsigned int denominator = 0;
	for (unsigned int i = 0; i < numModes; i++)
	{
		if (displayModeList[i].Width == (unsigned int)screenWidth)
		{
			if (displayModeList[i].Height == (unsigned int)screenHeight)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	D3D_DRIVER_TYPE driverTypes[] = {
	D3D_DRIVER_TYPE_HARDWARE, // CPU And GPU
	D3D_DRIVER_TYPE_WARP, // �ֽ� CPU�θ�
	D3D_DRIVER_TYPE_REFERENCE // CPU��
	};

	UINT DriverSize = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	UINT FeatureSize = ARRAYSIZE(featureLevels);


	//����ī���� ����ü
	DXGI_ADAPTER_DESC adapterDesc;
	if (FAILED(adapter->GetDesc(&adapterDesc)))
	{
		MessageBox(NULL, L"Cannot Read Video Card.", L"Error", MB_OK);
		return false;
	}

	// ����ī�� �޸� �뷮 ������ �ް�����Ʈ ������ ����
	m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	// ���� ī�� �̸� ����
	size_t stringLength = 0;
	if (wcstombs_s(&stringLength, m_videoCardDescription, 128, adapterDesc.Description, 128) != 0)
	{
		MessageBox(NULL, L"Cannot Save Video Card Name.", L"Error", MB_OK);
		return false;
	}

	delete[] displayModeList;
	displayModeList = 0;

	adapterOutput->Release();
	adapterOutput = 0;

	adapter->Release();
	adapter = 0;

	factory->Release();
	factory = 0;

	// ����ü�� ����ü �ʱ�ȭ
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// ����۴� 1����
	swapChainDesc.BufferCount = 1;

	// ������� ���̿� ���� ����
	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;

	// 32bit surface ����
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;

	// ������� ���ΰ�ħ ���� ����
	if (m_vsync_enabled)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	// ����� ���뵵�� ����
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// ������ �ڵ� ����
	swapChainDesc.OutputWindow = hWnd;

	// ��Ƽ���ø� x
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	// â��� ����
	if (fullscreen)
	{
		swapChainDesc.Windowed = false;
	}
	else
	{
		swapChainDesc.Windowed = true;
	}

	// ��ĵ ���� ���� �� ũ�⸦ �������� �������� ����
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// ��µ� ���� ����۸� ��쵵�� ����
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// �߰� �ɼ� �÷��׸� ������� �ʽ��ϴ�
	swapChainDesc.Flags = 0;

	// ��ó������ directx 11��
	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
	
	HRESULT hr;
	for (int i = 0; i < DriverSize; i++)
	{
		// ���� ü��, Direct3D ��ġ �� Direct3D ��ġ ���ؽ�Ʈ�� ����
		hr = D3D11CreateDeviceAndSwapChain(nullptr, driverTypes[i], nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT, featureLevels, FeatureSize,
			D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device, &m_featureLevel, &m_deviceContext);
		if (SUCCEEDED(hr))
		{
			break;
		}
	}
	if (FAILED(hr))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Create SwapChain.", L"Error", MB_OK);
#endif
		return false;
	}

	// �� ���� ������
	ID3D11Texture2D* backBufferPointer = nullptr;
	if (FAILED(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPointer)))
	{
		MessageBox(NULL, L"Cannot Get BackBufferPointer", L"Error", MB_OK);
		return false;
	}

	// �� ���� �����ͷ� ���� Ÿ�� �並 ����
	if (FAILED(m_device->CreateRenderTargetView(backBufferPointer, NULL, &m_renderTargetView)))
	{
		MessageBox(NULL, L"Cannot Create RenderTargetView", L"Error", MB_OK);
		return false;
	}

	// ����� ������ ����
	backBufferPointer->Release();
	backBufferPointer = 0;

	// ���� ���� ����ü �ʱ�ȭ
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// ���� ���� ����ü �ۼ�
	depthBufferDesc.Width = screenWidth;
	depthBufferDesc.Height = screenHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	// ������ ���̹��� ����ü�� ����Ͽ� ���� ���� �ؽ��� ����
	if (FAILED(m_device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer)))
	{
		MessageBox(NULL, L"Cannot Create DepthBuffer", L"Error", MB_OK);
		return false;
	}

	// ���ٽ� ���� ����ü �ʱ�ȭ
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// ���ٽ� ���� ����ü�� �ۼ�
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// �ȼ� ������ ���ٽ� ����
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// �ȼ� �޸��� ���ٽ� ����
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// ���� ���ٽ� ���¸� ����
	if (FAILED(m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState)))
	{
		MessageBox(NULL, L"Cannot Create Depth Stencil State", L"Error", MB_OK);
		return false;
	}

	// ���� ���ٽ� ���¸� ����
	m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

	// ���� ���ٽ� ���� ����ü�� �ʱ�ȭ�մϴ�
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// ���� ���ٽ� �� ����ü�� ����
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// ���� ���ٽ� �並 ����
	if (FAILED(m_device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc,
		&m_depthStencilView)))
	{
		MessageBox(NULL, L"Cannot Create Stencil View.", L"Error", MB_OK);
		return false;
	}

	// ������ ��� ��� ����  ���ٽ� ���۸� ��� ���� ������ ���ο� ���ε�
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	// �׷����� ������� ����� ������ ������ ����ü�� ����
	D3D11_RASTERIZER_DESC rasterDesc;
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// ������ ������ ���¸� ����
	if (FAILED(m_device->CreateRasterizerState(&rasterDesc, &m_rasterState)))
	{
		MessageBox(NULL, L"Cannot Create RasterizerState.", L"Error", MB_OK);
		return false;
	}

	// ���� ������ ������ ���� ����
	m_deviceContext->RSSetState(m_rasterState);

	// ����Ʈ ����
	D3D11_VIEWPORT viewport;
	viewport.Width = (float)screenWidth;
	viewport.Height = (float)screenHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	// ����Ʈ�� ����
	m_deviceContext->RSSetViewports(1, &viewport);

	// ���� ��� ����
	float fieldOfView = 3.141592654f / 4.0f;
	float screenAspect = (float)screenWidth / (float)screenHeight;

	// 3D �������� ���� ���� ���
	m_projectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenDepth);

	// ���� ����� �׵� ��ķ�
	m_worldMatrix = XMMatrixIdentity();

	m_worldMatrix = XMMatrixRotationX((-90) * (3.141592 / 180.0f));

	// 2D �������� ���� ���� ���� ���
	m_orthoMatrix = XMMatrixOrthographicLH((float)screenWidth, (float)screenHeight, screenNear, screenDepth);

	return CreateStecilBufferForRTT();
}

void DirectXEngine::Release()
{
	if (m_swapChain)
	{
		m_swapChain->SetFullscreenState(false, NULL);
	}

	// RTT --------------------------------------------
	if (m_alphaEnableBlendingState)
	{
		m_alphaEnableBlendingState->Release();
		m_alphaEnableBlendingState = 0;
	}

	if (m_alphaDisableBlendingState)
	{
		m_alphaDisableBlendingState->Release();
		m_alphaDisableBlendingState = 0;
	}
	//-------------------------------------------------

	if (m_rasterState)
	{
		m_rasterState->Release();
		m_rasterState = 0;
	}

	if (m_depthStencilView)
	{
		m_depthStencilView->Release();
		m_depthStencilView = 0;
	}

	// RTT ---------------------------------------------
	if (m_depthDisabledStencilState)
	{
		m_depthDisabledStencilState->Release();
		m_depthDisabledStencilState = 0;
	}
	// -------------------------------------------------

	if (m_depthStencilState)
	{
		m_depthStencilState->Release();
		m_depthStencilState = 0;
	}

	if (m_depthStencilBuffer)
	{
		m_depthStencilBuffer->Release();
		m_depthStencilBuffer = 0;
	}

	if (m_renderTargetView)
	{
		m_renderTargetView->Release();
		m_renderTargetView = 0;
	}

	if (m_deviceContext)
	{
		m_deviceContext->Release();
		m_deviceContext = 0;
	}

	if (m_device)
	{
		m_device->Release();
		m_device = 0;
	}

	if (m_swapChain)
	{
		m_swapChain->Release();
		m_swapChain = 0;
	}
}
bool DirectXEngine::Frame()
{
	return true;
}

bool DirectXEngine::Render()
{
	this->BeginScene();
	this->EndScene();
	return true;
}

void DirectXEngine::BeginScene()
{
	// ���۸� ��� ������ ������ �÷� ����
	float color[4] = { 0.5f, 0.5f, 0.5f, 1.0f };

	// ����� �ʱ�ȭ
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);

	// ���� ���� �ʱ�ȭ
	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void DirectXEngine::EndScene()
{
	// ������ �Ϸ��̹Ƿ� �� ���� ����
	if (m_vsync_enabled)
	{
		// ȭ�� ���� ��ħ ���� ����
		m_swapChain->Present(1, 0);
	}
	else
	{
		// ������ ������ ���
		m_swapChain->Present(0, 0);
	}
}

ID3D11Device* DirectXEngine::GetDevice()
{
	return m_device;
}

ID3D11DeviceContext* DirectXEngine::GetDeviceContext()
{
	return m_deviceContext;
}

IDXGISwapChain* DirectXEngine::GetSwapChain()
{
	return m_swapChain;
}

void DirectXEngine::GetProjectionMatrix(XMMATRIX& projectionMatrix)
{
	projectionMatrix = m_projectionMatrix;
}
void DirectXEngine::GetWorldMatrix(XMMATRIX& worldMatrix)
{
	worldMatrix = m_worldMatrix;
}

void DirectXEngine::GetOrthoMatrix(XMMATRIX& orthoMatrix)
{
	orthoMatrix = m_orthoMatrix;
}

void DirectXEngine::GetVideoCardInfo(char* cardName, int& memory)
{
	strcpy_s(cardName, 128, m_videoCardDescription);
	memory = m_videoCardMemory;
}

int DirectXEngine::GetHeight()
{
	return screenHeight;
}

int DirectXEngine::GetWidth()
{
	return screenWidth;
}

float DirectXEngine::GetScreenDepth()
{
	return screenDepth;
}

float DirectXEngine::GetScreenNear()
{
	return screenNear;
}

void DirectXEngine::TurnZBufferOn()
{
	m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);
}

void DirectXEngine::TurnZBufferOff()
{
	m_deviceContext->OMSetDepthStencilState(m_depthDisabledStencilState, 1);
}

//RTT ------------------------------------------
bool DirectXEngine::CreateStecilBufferForRTT()
{
	D3D11_DEPTH_STENCIL_DESC depthDisabledStencilDesc;
	ZeroMemory(&depthDisabledStencilDesc, sizeof(depthDisabledStencilDesc));

	depthDisabledStencilDesc.DepthEnable = false;
	depthDisabledStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthDisabledStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthDisabledStencilDesc.StencilEnable = true;
	depthDisabledStencilDesc.StencilReadMask = 0xFF;
	depthDisabledStencilDesc.StencilWriteMask = 0xFF;
	depthDisabledStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthDisabledStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthDisabledStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthDisabledStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	if (FAILED(m_device->CreateDepthStencilState(&depthDisabledStencilDesc, &m_depthDisabledStencilState)))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Create RTT Stencil State.", L"Error", MB_OK);
#endif
		return false;
	}

	D3D11_BLEND_DESC blendStateDescription;
	ZeroMemory(&blendStateDescription, sizeof(blendStateDescription));

	blendStateDescription.RenderTarget[0].BlendEnable = TRUE;
	blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].RenderTargetWriteMask = 0x0f;

	if (FAILED(m_device->CreateBlendState(&blendStateDescription, &m_alphaEnableBlendingState)))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Create RTT Blend State.", L"Error", MB_OK);
#endif
		return false;
	}

	blendStateDescription.RenderTarget[0].BlendEnable = FALSE;

	if(FAILED(m_device->CreateBlendState(&blendStateDescription, &m_alphaDisableBlendingState)))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Create RTT Blend Second State.", L"Error", MB_OK);
#endif
		return false;
	}

	return true;
}

void DirectXEngine::TurnOnAlphaBlending()
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	m_deviceContext->OMSetBlendState(m_alphaEnableBlendingState, blendFactor, 0xffffffff);
}

void DirectXEngine::TurnOffAlphaBlending()
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	m_deviceContext->OMSetBlendState(m_alphaDisableBlendingState, blendFactor, 0xffffffff);
}

ID3D11DepthStencilView* DirectXEngine::GetDepthStencilView()
{
	return m_depthStencilView;
}

void DirectXEngine::SetBackBufferRenderTarget()
{
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
}

void DirectXEngine::OnResize(int width, int height)
{
	m_deviceContext->OMSetRenderTargets(0, 0, 0);

	// Release all outstanding references to the swap chain's buffers.
	m_renderTargetView->Release();

	HRESULT hr;
	// Preserve the existing buffer count and format.
	// Automatically choose the width and height to match the client rect for HWNDs.
	hr = m_swapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);

	// Perform error handling here!
	if (FAILED(hr))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Resize Buffer.", L"Error", MB_OK);
#endif
		PostQuitMessage(0);
		return;
	}
	// Get buffer and create a render-target-view.
	ID3D11Texture2D* pBuffer;
	hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
		(void**)&pBuffer);
	// Perform error handling here!
	if (FAILED(hr))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Get Buffer in Resizing.", L"Error", MB_OK);
#endif
		PostQuitMessage(0);
		return;
	}


	hr = m_device->CreateRenderTargetView(pBuffer, NULL,
		&m_renderTargetView);
	// Perform error handling here!
	if (FAILED(hr))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Create Render Target in Resizing.", L"Error", MB_OK);
#endif
		PostQuitMessage(0);
		return;
	}
	pBuffer->Release();

	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, NULL);

	// Set up the viewport.
	D3D11_VIEWPORT vp;
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_deviceContext->RSSetViewports(1, &vp);
}

bool DirectXEngine::OnResize(HWND hWnd, GameOption* gameOption)
{
	this->Release();
	return this->Initialize(gameOption->GetWidth(), gameOption->GetHeight(), hWnd, gameOption->GetFullScreen());
}