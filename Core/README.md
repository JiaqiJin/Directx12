# Chapter One

## Header files and reference library files
###### To call D3D12, the first step is to include header file and link all the lib.

```
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN // Exclude rarely used data from the Windows header
#include <windows.h>
#include <tchar.h>
//Adding wrl support to facility the use of COM
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
 
#include "..\WindowsCommons\d3dx12.h"
 
#define KAWAII_WND_CLASS_NAME _T("Game Window Class")
#define KAWAII_WND_TITLE   _T("DirectX12 Trigger Sample")
 
#define KAWAII_THROW_IF_FAILED(hr) if (FAILED(hr)){ throw KAWASCOMException(hr); }
```

The above code is the whole preparation.

First of all , the code include WRL, specially when calling COM componente interface, it brings a basic security conveniences(forget about Release 
calls, no bring some memory lake problems).

Secondly, we include the <DirectxMath.h> header file, which provides SIMD(note that is more powerful than tought,because it uses almost all modern CPUs efficiently through assembly language The SIMD extension 
instruction on the above, and it is an inline function form, is an important extension library for draining the CPU) 
C++ types and functions for common linear algebra and graphics math operation common to DirectX applications.

The other thing, I'm using #pragma comment(lib ,"xxxx") to refer some lib library. The project contains "d3d12.h" file, this file is derive form the 
structure of the D3D12 as simple class for ease use, the encapsulation should be part of D3D12 sdk, you can found it from the latest Microsoft D3D12 example.
In fact, the encapsulation here is not counter as encapsulation. It just means that the original structure is changed to a class and the constructor is added.
Of course, if you wanted to undestand some of the parameter of the D3D12 structure in mpre detail, i suggest that you dont include it.

Finally, the macro KAWAII_THROW_IF_FAILED is actually a macro used to simplify the handling of errors when calling the COM interface. It is to throw an exception when an error occurs, 
because as long as the language has an exception mechanism, programmers will use throwing exceptions. 

# Define the 3D data structure 

```
struct KAWAII_VERTEX
{
XMFLOAT3 position;
XMFLOAT4 color;
};

```
XMFLOAT3 and XMFLOAT4 come from the DirectXMath library, which is equivalent to float[3] and float[4].

# Define the variables


