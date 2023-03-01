#pragma once
#if _WIN32
#include <Windows.h>
#include <ag/native/win32/d3dx12.hpp>
#include <d3d12.h>
#include <d3dcompiler.h>
#include <dxgi1_6.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;

#endif