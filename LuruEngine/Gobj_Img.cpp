#include "Gobj_Img.h"

namespace sg
{
	Gobj_Img::Gobj_Img()
		: mTr(nullptr)
		, mMr(nullptr)
	{
		SetName(L"Gobj_Img");
		AddComp<MeshRenderer>();
	}
	Gobj_Img::~Gobj_Img()
	{
	}
	void Gobj_Img::Initialize()
	{
		GameObject::Initialize();
	}
	void Gobj_Img::Update()
	{
		GameObject::Update();
	}
	void Gobj_Img::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Gobj_Img::Render()
	{
		GameObject::Render();
	}
}