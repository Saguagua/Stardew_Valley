// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
#include <wrl/client.h>
#include <functional>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")

using namespace std;
using namespace DirectX;
using namespace Microsoft::WRL;

//Math
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Transform.h"

//Device
#include "Framework/Device/Device.h"

//Collider

//Render
#include "Framework/Render/InputLayout.h"
#include "Framework/Render/ConstantBuffer.h"
#include "Framework/Render/Buffers.h"
#include "Framework/Render/VertexBuffer.h"
#include "Framework/Render/IndexBuffer.h"
#include "Framework/Render/Shader.h"
#include "Framework/Render/VertexShader.h"
#include "Framework/Render/PixelShader.h"
#include "Framework/Render/ShaderManager.h"

//Utility
#include "Framework/Utility/Timer.h"
#include "Framework/Utility/InputManager.h"

#include "Scene/Scene.h"

#include "Program/Program.h"

#include "Types.h"

extern HWND hWnd;
