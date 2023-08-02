#include "Tile_Tile.h"
#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgCamera.h"
#include "..\Engine_SOURCE\sgResources.h"
#include "..\Engine_SOURCE\sgTexture.h"
#include "Tile_TilePalette.h"
#include "SCRIPT_Tile0.h"
#include "SCRIPT_Tile1.h"

namespace sg
{
	Tile::Tile()
		: mAtlas(nullptr)
		, mIndex(-1)
		, mX(0)
		, mY(0)
		, mZ(0)
		, mCB{}
		, mTr(nullptr)
		, mMr(nullptr)
		, mCol(nullptr)
	{		
		SetName(L"Tile");
	}
	Tile::Tile(Vector3 pos)
		: mAtlas(nullptr)
		, mIndex(-1)
		, mX(0)
		, mY(0)
		, mZ(0)
		, mCB{}
		, mTr(nullptr)
		, mMr(nullptr)
		, mCol(nullptr)
	{

		SetName(L"Tile");

		GetComp<Transform>()->SetPosition(pos);
	}
	Tile::~Tile()
	{
	}
	void Tile::InitializeTile(std::shared_ptr<Texture> atlas, int index)
	{
		mIndex = index;
		if (atlas == nullptr || index < 0)
			return;


		mAtlas = atlas;
		SetIndex(index);

		mTr = GetComp<Transform>();
		mTr->SetScale(9.0f, 9.0f, 1.0f);
		mCB = {};
		mCB.TileIndex = mIndex;

		if (mIndex == 0)
		{
			mCol = AddComp<Collider2D>();
			this->AddComp<SCRIPT_Tile0>();
		}

		if (mIndex == 1)
		{
			mCol = AddComp<Collider2D>();
			this->AddComp<SCRIPT_Tile1>();
		}

	}
	void Tile::SetIndex(int index)
	{
		int maxCol = (int)mAtlas->GetWidth() / TILE_SIZE_X;
		int maxRow = (int)mAtlas->GetHeight() / TILE_SIZE_Y;

		mY = index / maxCol;
		mX = index % maxCol;
	}
	void Tile::Update()
	{
		GameObject::Update();
	}
	void Tile::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Tile::Render()
	{
		ConstantBuffer* MyCB = renderer::constantBuffer[(UINT)eCBType::MyCBType];
		MyCB->SetData(&mCB);
		MyCB->Bind(eShaderStage::PS);

		GameObject::Render();
	}

}