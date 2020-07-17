#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "d3dUtil.h"
#include "GameTimer.h"

class D3D12App
{
protected :
	D3D12App(HINSTANCE hInstance);
	D3D12App& operator=(const D3D12App& rhs) = delete;
	D3D12App(const D3D12App& rhs) = delete;
	virtual ~D3D12App();

public:
	static D3D12App* GetApp(); //return app
	HINSTANCE AppInst()const;
	HWND      MainWnd()const;
	float     AspectRatio()const;

	int Run();

	virtual bool Initialize();

	bool Get4xMsaaState() const;
	void Set4xMsaaState(bool value);

	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	//Main function
	bool InitMainWindow();
	bool InitDirect3D();
	void CreateRtvAndDsvDescriptorHeaps();
	virtual void OnResize();

	// Convenience overrides for handling mouse input.
	virtual void OnMouseDown(WPARAM btnState, int x, int y) { }
	virtual void OnMouseUp(WPARAM btnState, int x, int y) { }
	virtual void OnMouseMove(WPARAM btnState, int x, int y) { }

protected:
	//Functions
	void CreateCommandObjects();
	void CreateSwapChain();
	
	void FlushCommandQueue();
	 
	//get back buffer of back RTV and DSV
	D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView()const;
	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView()const;

	ID3D12Resource* CurrentBackBuffer() const;

	void LogAdapters();
	void LogAdapterOutputs(IDXGIAdapter* adapter);
	void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);

	void CalculateFrameStats();
	virtual void Update(const GameTimer& gt) = 0;
	virtual void Draw(const GameTimer& gt) = 0;

protected:
	//Variables

	static D3D12App* mApp;

	HINSTANCE mhAppInst = nullptr; // application instance handle
	HWND      mhMainWnd = nullptr; // main window handle
	bool      mAppPaused = false;  // is the application paused?
	bool      mMinimized = false;  // is the application minimized?
	bool      mMaximized = false;  // is the application maximized?
	bool      mResizing = false;   // are the resize bars being dragged?
	bool      mFullscreenState = false;// fullscreen enabled

	// Used to keep track of the delta-time?and game time (?.4).
	GameTimer mTimer;
	//Device
	Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
	Microsoft::WRL::ComPtr<IDXGIFactory4> mdxgiFactory;
	Microsoft::WRL::ComPtr<ID3D12Device> md3dDevice;

	//Fence for CPU/GPU synchronization.
	Microsoft::WRL::ComPtr<ID3D12Fence> mFence;
	UINT64 mCurrentFence = 0; // the initial fence value is 0

	//The desciprto heap is use for resource for GPU, and this can obtain resource data and othe info.
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mRtvHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mDsvHeap;
	UINT mRtvDescriptorSize = 0;
	UINT mDsvDescriptorSize = 0;
	UINT mCbvSrvUavDescriptorSize = 0;

	//resource for the rtv and dsv
	int mCurrBackBuffer = 0;
	static const int SwapChainBufferCount = 2;
	Microsoft::WRL::ComPtr<ID3D12Resource> mSwapChainBuffer[SwapChainBufferCount];
	Microsoft::WRL::ComPtr<ID3D12Resource> mDepthStencilBuffer;

	//4X MSAA
	bool      m4xMsaaState = false;    // 4X MSAA enabled
	UINT      m4xMsaaQuality = 0;      // quality level of 4X MSAA

	//Coomand objetc
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> mCommandQueue; // submititing the command list, excution ...(GPU)
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> mDirectCmdListAlloc; //storage for GPU commands 
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> mCommandList; //Encapsulates a list of graphics commands for rendering (CPU)

	D3D12_VIEWPORT mScreenViewport;
	D3D12_RECT mScissorRect;

	std::wstring mMainWndCaption = L"d3d App";
	int mClientWidth = 800;
	int mClientHeight = 600;
	DXGI_FORMAT mBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	DXGI_FORMAT mDepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

};