#include "Tile_Tile.h"
#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgCamera.h"
#include "..\Engine_SOURCE\sgResources.h"
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
	void Tile::InitializeTile(std::shared_ptr<Texture> atlas, int index)
	{
		mMr = AddComp<MeshRenderer>();
		std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"Cat");
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
		mMr->SetMaterial(material);
		mMr->Initialize();
		
		mIndex = index;
		if (atlas == nullptr || index < 0)
			return;

		mAtlas = texture;
		SetIndex(index);

	}
	void Tile::SetIndex(int index)
	{
		int maxCol = mAtlas->GetWidth() / TILE_SIZE_X;
		int maxRow = mAtlas->GetHeight() / TILE_SIZE_Y;

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
		GameObject::Render();
	}
}