
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN // 从 Windows 头中排除极少使用的资料
#include <windows.h>
#include <tchar.h>
//添加WTL支持 方便使用COM
#include <wrl.h>
using namespace Microsoft;
using namespace Microsoft::WRL;
#include <dxgi1_6.h>
#include <DirectXMath.h>
using namespace DirectX;
//for d3d12
#include <d3d12.h>
#include <d3d12shader.h>
#include <d3dcompiler.h>
//linker
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d3dcompiler.lib")

#if defined(_DEBUG)
#include <dxgidebug.h>
#endif

#include "../WindowsCommons/d3dx12.h"

#define KAWAII_WND_CLASS_NAME _T("Game Window Class")
#define KAWAII_WND_TITLE	_T("DirectX12 Trigger Example")

#define KAWAII_THROW_IF_FAILED(hr) if (FAILED(hr)){ throw CGRSCOMException(hr); }

struct KAWAII_VERTEX
{
	XMFLOAT4 m_vtPos;
	XMFLOAT4 m_vtColor;

};

int main()
{
	return 0;
}

