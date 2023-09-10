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
#include <algorithm>
#include <wrl/client.h>
#include <fstream>
#include <functional>
#include <random>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")

#include "DirectXTex.h"
#pragma comment(lib, "DirectXTex/DirectXTex.lib")

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#pragma comment(lib, "ImGui/ImGui.lib")

// FMOD
#include "Library/FMOD/inc/fmod.hpp"
#pragma comment(lib,"Library/FMOD/fmod_vc.lib")

using namespace std;
using namespace DirectX;
using namespace Microsoft::WRL;



#include "Defines.h"
#include "Enums.h"

//Math
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Transform.h"

//Device
#include "Framework/Device/Device.h"

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

//TextureMapping
#include "Framework/TextureMapping/SRV.h"
#include "Framework/TextureMapping/SamplerState.h"
#include "Framework/TextureMapping/BlendState.h"
#include "Framework/TextureMapping/SRVManager.h"
#include "Framework/TextureMapping/StateManager.h"

//Informations
#include "Data/DataInfos.h"
//Save
#include "Data/DataManager.h"

//BasicObject
#include "Object/BasicObj/ShapeLine.h"
#include "Object/BasicObj/CircleLine.h"
#include "Object/BasicObj/RectLine.h"
#include "Object/BasicObj/SingleColorRect.h"
#include "Object/BasicObj/TextureRect.h"
#include "Object/BasicObj/LightTextureRect.h"
#include "Object/BasicObj/Sprite.h"

//Collider
#include "Framework/Collision/Collider.h"
#include "Framework/Collision/CircleCollider.h"
#include "Framework/Collision/RectCollider.h"


//GameObject
#include "Object\GameObj\Others\GameObject.h"
#include "Object\GameObj\Others\DeployableObj/DeployableObject.h"
#include "Object\GameObj\Others\DeployableObj\BreakableItem.h"
#include "Object\GameObj\Others\DeployableObj/Crop.h"
#include "Object\GameObj\Others\DeployableObj/PickableItem.h"
#include "Object/GameObj/Others/DeployableObj/Bed.h"
#include "Object/GameObj/Others/DeployableObj/Door.h"
#include "Object/GameObj/Others/DeployableObj/Light.h"
#include "Object\GameObj\Others\DeployableObj\Wall.h"


#include "Object/Tile/Tile.h"

#include "Object\GameObj\Others\DeployableObj\DropItem.h"
#include "Object/GameObj/ObjectSpawner.h"

#include "Object\GameObj\Others\Items\Item.h"

//Animation
#include "Framework/Animation/Action.h"

//Effect
#include "Object/Effect/Effect.h"
#include "Object/Effect/DamageEffect.h"
#include "Object/Effect/EffectManager.h"

#include "Object\GameObj\Others\DeployableObj\FishingHook.h"
#include "Object\UI\FishingMinigame.h"

#include "Object\GameObj\Creature\Creature.h"

//Player
#include "Object/GameObj/Creature/Player/Player.h"
#include "Object/GameObj/Creature/Player/PlayerSubscribe.h"
#include "Object/GameObj/Creature/Player/PlayerImproved.h"
#include "Object\GameObj\Creature\Player\PlayerFight.h"

#include "Object\GameObj\Creature\Monsters\Monster.h"
#include "Object\GameObj\Creature\Monsters\Bat.h"
#include "Object/GameObj/Creature/Monsters/Slime.h"
#include "Object/GameObj/Creature/Monsters/MonsterSpawner.h"

//UI
#include "Object/UI/NumberUI.h"
#include "Object/UI/Button.h"
#include "Object/UI/ColorButton.h"
#include "Object/UI/TextureButton.h"
#include "Object\UI\List.h"
#include "Object/UI/PlayerUI.h"
#include "Object/UI/Palette.h"

//Map
#include "Map/TileMap.h"

//System
#include "Framework/System/FishingSystem.h"

//Camera
#include"Framework/Camera/Camera.h"

//Utility
#include "Framework/Utility/Timer.h"
#include "Framework/Utility/InputManager.h"

#include "Framework/Light/LightManager.h"

//Scene
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"

//Program
#include "Program/Program.h"


extern HWND _hWnd;