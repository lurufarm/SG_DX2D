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
			UINT32 x;
			UINT32 y;
		};
		UINT64 id;
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

		static Vector3 GetTilePos(Vector3 mousPos);
		static void SetIndex(UINT index) { mIndex = index; }
		static UINT GetIndex() { return mIndex; }

	private:
		static std::unordered_map<UINT64, Tile*> mTiles;
		static std::shared_ptr<Tile_Image> mImage;
		static UINT mIndex;
	};
}
