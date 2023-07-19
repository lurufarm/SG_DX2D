#pragma once
#include "Tile_Tile.h"
#include "..\Engine_SOURCE\\sgMaterial.h"
#include "..\Engine_SOURCE\\sgObject.h"

namespace sg
{
	union TileID
	{
		struct
		{
			INT32 x;
			INT32 y;
		};
		INT64 id;
	};

	class TilePalette
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();

		static void CreateTile(int index, Vector3 pos);
		static void CreateTiles(int index, UINT width, UINT height);
		static void Save();
		static void Load();
		static void AutoLoad(std::wstring path);
		static void Clear();

		static Vector3 GetTilePos(Vector3 mousPos);
		static void SetIndex(UINT index) { mIndex = index; }
		static UINT GetIndex() { return mIndex; }

	private:
		static std::unordered_map<UINT64, Tile*> mTiles;
		static std::shared_ptr<Texture> mImage;
		static UINT mIndex;
	};
}
