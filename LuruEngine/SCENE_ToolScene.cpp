#include "SCENE_ToolScene.h"
#include "..\Engine_SOURCE\sgApplication.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgResources.h"
#include "..\Engine_SOURCE\sgMaterial.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgCamera.h"

#include "Tile_Tile.h"
#include "Tile_Image.h"
#include "Tile_TilePalette.h"

extern sg::Application application;

namespace sg
{
	ToolScene::ToolScene()
	{
	}
	ToolScene::~ToolScene()
	{
	}
	void ToolScene::Initialize()
	{
		Scene::Initialize();
		TilePalette::Initialize();
	}
	void ToolScene::Update()
	{
		Scene::Update();

		Vector2 temp = Input::GetMousePos();

		if (Input::KeyD(eKeyCode::LBUTTON))
		{
			Vector2 mousePos = Input::GetMousePos();
			Vector3 pos = Vector3(mousePos.x, mousePos.y, 0.0f);
			pos = TilePalette::GetTilePos(Vector3(pos.x, pos.y, 0.0f));

			UINT tileIndex = TilePalette::GetIndex();
			TilePalette::CreateTile(tileIndex, pos);
		}

		if (Input::KeyD(eKeyCode::S))
		{
			TilePalette::Save();
		}
		if (Input::KeyD(eKeyCode::D))
		{
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
	}
	void ToolScene::OnExit()
	{
	}
}

#include "..\Editor_Window\Resource.h"
#include "..\Engine_SOURCE\sgResources.h"

LRESULT CALLBACK AtlasWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		std::shared_ptr<sg::Tile_Image> tile = sg::Resources::Load<sg::Tile_Image>(L"catt", L"..\\Resources\\catt.bmp");
		RECT rect = { 0, 0, tile->GetWidth(), tile->GetHeight() };
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

			int x = mousePos.x / TILE_SIZE_X;
			int y = mousePos.y / TILE_SIZE_Y;

			int index = (y * 8) + (x % 8);

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

		std::shared_ptr <sg::Tile_Image> tile = sg::Resources::Find<sg::Tile_Image>(L"catt");
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

