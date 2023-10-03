#include "SCENE_ToolScene.h"
#include "..\Engine_SOURCE\sgApplication.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgResources.h"
#include "..\Engine_SOURCE\sgMaterial.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgCamera.h"
#include "SCRIPT_CameraScript.h"

#include "Tile_Tile.h"
#include "Tile_Image.h"
#include "Tile_TilePalette.h"

#include "Img_Stage0_Forest01_Map.h"
#include "Img_LobbyMap.h"
#include "Interact_LobbyCharacter.h"
#include "Interact_LobbyUpgrade.h"
#include "Interact_LobbyCardBook.h"
#include "Interact_LobbyGate.h"
#include "Interact_Gate.h"
#include "Img_LobbyTorch.h"
#include "..\Engine_SOURCE\sgParticleSystem.h"

extern sg::Application application;

namespace sg
{
	ToolScene::ToolScene()
	{
		SetName(L"99_ToolScene");
	}
	ToolScene::~ToolScene()
	{
	}
	void ToolScene::Initialize()
	{
		Scene::Initialize();
		TilePalette::Initialize();

#pragma region Forest
		//Vector3 pos = Vector3(-11.0f, 5.0f, 0.0f);
		//object::Instantiate<Img_Stage0_Map>(Img_Stage0_Map::Stage0::forestfd04, pos, eLayerType::BGImg, this);
		object::Instantiate<Img_Stage0_Map>(Img_Stage0_Map::Stage0::forestdg01, /*pos,*/ eLayerType::BGImg, this);

#pragma endregion

		mToolSceneCamera = object::Instantiate<GameObject>(eLayerType::Tile, this);
		mToolSceneCamera->AddComp<Camera>();
		mToolSceneCamera->AddComp<SCRIPT_CameraScript>();

		GameObject* light = new GameObject();
		AddGameObj(eLayerType::Light, light);
		Light* lg = light->AddComp<Light>();
		lg->SetType(eLightType::Directional);
		lg->SetColor(Vector4(0.8f, 0.8f, 0.8f, 1.0f));

	}
	void ToolScene::Update()
	{
		Scene::Update();

		Vector3 temp = Input::GetMousePos();

		if (Input::KeyD(eKeyCode::B))
		{
			SceneManager::LoadScene(L"02_LobbyScene");
		}


		if (Input::KeyD(eKeyCode::LBUTTON))
		{
			Vector3 mousePos = Input::GetMousePos();
			Vector3 pos = Vector3(mousePos.x, mousePos.y, 0.0f);

			UINT tileIndex = TilePalette::GetIndex();
			Vector3 tilePos = Vector3::Zero;
			tilePos.x = (int)(Input::GetFinalMousePos().x) - (int)Input::GetFinalMousePos().x % TILE_SIZE_X;
			tilePos.y = (int)(Input::GetFinalMousePos().y) - (int)Input::GetFinalMousePos().y % TILE_SIZE_Y;
			tilePos.z = 0.0f;
			TilePalette::CreateTile(tileIndex, tilePos);
		}
		if (Input::KeyD(eKeyCode::RBUTTON))
		{
			Vector3 mousePos = Input::GetMousePos();
			Vector3 pos = Vector3(mousePos.x, mousePos.y, 0.0f);

			Vector3 tilePos = Vector3::Zero;
			tilePos.x = (int)(Input::GetFinalMousePos().x) - (int)Input::GetFinalMousePos().x % TILE_SIZE_X;
			tilePos.y = (int)(Input::GetFinalMousePos().y) - (int)Input::GetFinalMousePos().y % TILE_SIZE_Y;
			tilePos.z = 0.0f;

			TilePalette::DeleteTile(tilePos);
		}


		if (Input::KeyD(eKeyCode::Z))
		{
			TilePalette::Save();
		}
		if (Input::KeyD(eKeyCode::L))
		{
			TilePalette::Clear();
			TilePalette::Load();
		}
	}
	void ToolScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void ToolScene::Render()
	{
		
		Scene::Render();
	}
	void ToolScene::OnEnter()
	{
		renderer::mainCamera = mToolSceneCamera->GetComp<Camera>();
	}
	void ToolScene::OnExit()
	{
	}
}

#include "..\Editor_Window\Resource.h"
#include "..\Engine_SOURCE\sgResources.h"
#include "..\Engine_SOURCE\sgInput.h"

std::shared_ptr<sg::Tile_Image> tileAtlas = std::make_shared<sg::Tile_Image>();

LRESULT CALLBACK AtlasWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		tileAtlas = sg::Resources::Load<sg::Tile_Image>(L"TilePalette", L"..\\Resources\\Tile\\tilepalette.bmp");

		RECT rect = { 0, 0, tileAtlas->GetWidth(), tileAtlas->GetHeight() };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		SetWindowPos(hWnd
			, nullptr, 1600, 0
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);
		ShowWindow(hWnd, true);
	}
	case WM_LBUTTONDOWN:
	{
		if (GetFocus())
		{
			::POINT mousePos = {};
			::GetCursorPos(&mousePos);
			::ScreenToClient(application.GetToolHwnd(), &mousePos);

			//int x = (int)mousePos.x / TILE_SIZE_X;
			//int y = (int)mousePos.y / TILE_SIZE_Y;

			//int index = (y * 10) + (x % 10);

			int x = mousePos.x / 18;
			int y = mousePos.y / 18;

			int MAX_X = tileAtlas->GetWidth() / 18;
			int MAX_Y = tileAtlas->GetHeight() / 18;

			int index = (y * MAX_X) + (x % MAX_X);

			sg::TilePalette::SetIndex(index);
		}
	}
	break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);

		switch (wmId)
		{
			break;
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		std::shared_ptr <sg::Tile_Image> tile = sg::Resources::Find<sg::Tile_Image>(L"TilePalette");
		BitBlt(hdc, 0, 0, tile->GetWidth(), tile->GetHeight(),
			tile->GetHdc(), 0, 0, SRCCOPY);

		EndPaint(hWnd, &ps);
		break;
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

