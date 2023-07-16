#include "Tile_TilePalette.h"
#include "..\Engine_SOURCE\sgResources.h"
#include "..\Engine_SOURCE\sgInput.h"
#include <commdlg.h>

namespace sg
{
	std::shared_ptr<Material> TilePalette::mMaterial = nullptr;
	std::unordered_map<UINT64, Tile*> TilePalette::mTiles = {};
	UINT TilePalette::mIndex = -1;

	void TilePalette::Initialize()
	{
		mMaterial = Resources::Find<Material>(L"");
	}
	void TilePalette::Update()
	{
	}
	void TilePalette::LateUpdate()
	{
	}
	void TilePalette::Render()
	{
	}
	void TilePalette::CreateTile(int index, Vector3 pos)
	{
		Vector2 mousePos = Input::GetMousePos();
		if (mousePos.x >= 1600.0f || mousePos.x <= 0.0f)
			return;
		if (mousePos.y >= 900.0f || mousePos.y <= 0.0f)
			return;

		Tile* tile = object::Instantiate<Tile>(eLayerType::Tile, SceneManager::GetActiveScene());
		tile->InitializeTile(mMaterial, index);

		Vector3 tilePos(pos.x * TILE_SIZE_X, pos.y * TILE_SIZE_Y, TILE_SIZE_X);
		tile->GetComp<Transform>()->SetPosition(tilePos);

		TileID id;
		id.x = (UINT32)pos.x;
		id.y = (UINT32)pos.y;

		mTiles.insert(std::make_pair(id.id, tile));
	}
	void TilePalette::CreateTiles(int index, UINT width, UINT height)
	{
	}
	void TilePalette::Save()
	{
		// open a file name
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"Tile\0*.tile\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetSaveFileName(&ofn))
			return;

		// 파일 입출력
		FILE* file = nullptr;

		// 쓰기 모드로 열기
		_wfopen_s(&file, szFilePath, L"wb");

		if (nullptr == file)
			return;

		std::unordered_map<UINT64, Tile*>::iterator iter = mTiles.begin();
		for (; iter != mTiles.end(); iter++)
		{
			int index = iter->second->Index();
			fwrite(&index, sizeof(int), 1, file);

			TileID id;
			id.id = iter->first;
			fwrite(&id.id, sizeof(TileID), 1, file);
		}

		fclose(file);
	}
	void TilePalette::Load()
	{
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetOpenFileName(&ofn))
			return;

		FILE* file = nullptr;
		_wfopen_s(&file, szFilePath, L"rb");

		if (file == nullptr)
			return;

		while (true)
		{
			int index = -1;
			TileID id;

			if (fread(&index, sizeof(int), 1, file) == NULL)
				break;

			if (fread(&id.id, sizeof(TileID), 1, file) == NULL)
				break;

			CreateTile(index, Vector3(id.x, id.y, 0));
		}

		fclose(file);
	}
	Vector3 TilePalette::GetTilePos(Vector3 mousePos)
	{
		int indexY = mousePos.y / TILE_SIZE_Y;
		int indexX = mousePos.x / TILE_SIZE_X;

		return Vector3(indexX, indexY, 0);
	}
}