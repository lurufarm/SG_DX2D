#include "Tile_Tile.h"
#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgCamera.h"
#include "..\Engine_SOURCE\sgTexture.h"



namespace sg
{
	Tile::Tile()
		: mAtlas(nullptr)
		, mIndex(-1)
		, mX(0)
		, mY(0)
		, mZ(0)
	{
	}
	Tile::Tile(Vector3 pos)
		: mAtlas(nullptr)
		, mIndex(-1)
		, mX(0)
		, mY(0)
		, mZ(0)
	{
		GetComp<Transform>()->SetPosition(pos);
	}
	Tile::~Tile()
	{
	}
	void Tile::InitializeTile(std::shared_ptr<Material> atlas, int index)
	{
		mIndex = index;
		if (atlas == nullptr || index < 0)
			return;

		mAtlas = atlas;
		SetIndex(index);
	}
	void Tile::SetIndex(int index)
	{	
		int maxCol = mAtlas->GetTexture()->GetWidth() / TILE_SIZE_X;
		int maxRow = mAtlas->GetTexture()->GetHeight() / TILE_SIZE_Y;
	
		mY = index / maxCol;
		mX = index % maxCol;
	}
	void Tile::Update()
	{
	}
	void Tile::LateUpdate()
	{
	}
	void Tile::Render()
	{
		
	}
}