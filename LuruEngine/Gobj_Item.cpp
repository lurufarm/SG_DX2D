#include "Gobj_Item.h"
#include <random>

namespace sg
{
	Gobj_Item::Gobj_Item()
	{
		AddComp<MeshRenderer>();
		AddComp<Collider2D>();
		AddComp<Animator>();
		SetMesh();
		SetMaterial(L"AnimationMaterial");
		mPlayer = Player;
	}
	Gobj_Item::~Gobj_Item()
	{
	}
	void Gobj_Item::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
	}
	void Gobj_Item::Update()
	{
		GameObject::Update();
	}
	void Gobj_Item::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Gobj_Item::Render()
	{
		GameObject::Render();
	}
	UINT Gobj_Item::RandomNumber(int a, int b)
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		// 0부터 10까지의 분포 설정
		std::uniform_int_distribution<> dis(a, b);

		return dis(gen);
	}
}