#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include "PredefinedGuid.h"

extern const int WIN_WIDTH;
extern const int WIN_HEIGHT;
const int FRAME_COUNT = 2;

ID3D12Device* gDevice;
ID3D12CommandQueue* gCommandQueue;

void InitDx(HWND hWnd)
{
	UINT dxgiFactoryFlags = 0;
#ifdef _DEBUG
	ID3D12Debug* debug = 0;
	if (SUCCEEDED(D3D12GetDebugInterface(&IID_ID3D12Debug, (void**)&debug)))
	{
		debug->lpVtbl->EnableDebugLayer(debug);
		dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
		debug->lpVtbl->Release(debug);
		debug = 0;
	}
#endif

	D3D12CreateDevice(NULL, D3D_FEATURE_LEVEL_11_0, &IID_ID3D12Device, (void**)&gDevice);
	if (gDevice == 0)
	{
		return;
	}

	D3D12_COMMAND_QUEUE_DESC queueDesc = { 0, };
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	gDevice->lpVtbl->CreateCommandQueue(gDevice, &queueDesc, &IID_ID3D12CommandQueue, (LPVOID*)&gCommandQueue);

	IDXGIFactory4* pFactory;
	CreateDXGIFactory2(dxgiFactoryFlags, &IID_IDXGIFactory4, (LPVOID*)&pFactory);
	if (pFactory == 0)
	{
		return;
	}

	DXGI_SWAP_CHAIN_DESC1 descSwapChain = { 0, };
	descSwapChain.BufferCount = FRAME_COUNT;
	descSwapChain.Width = WIN_WIDTH;
	descSwapChain.Height = WIN_HEIGHT;
	descSwapChain.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	descSwapChain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	descSwapChain.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	descSwapChain.SampleDesc.Count = 1;

	IDXGISwapChain1* pSwapChain;
	pFactory->lpVtbl->CreateSwapChainForHwnd(pFactory,
		(IUnknown*)gCommandQueue,
		hWnd,
		&descSwapChain,
		NULL,
		NULL,
		&pSwapChain);

	pFactory->lpVtbl->Release(pFactory);
	pSwapChain->lpVtbl->Release(pSwapChain);
}

void ClearDx()
{
	gDevice->lpVtbl->Release(gDevice);
	gCommandQueue->lpVtbl->Release(gCommandQueue);
}