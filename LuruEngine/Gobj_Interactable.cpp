#include "Gobj_Interactable.h"

namespace sg
{
	Gobj_Interactable::Gobj_Interactable()
		: mTr(nullptr)
		, mMr(nullptr)
		, mCol(nullptr)
	{
		SetName(L"Gobj_Interactable");
		AddComp<MeshRenderer>();
		AddComp<Collider2D>();
	}
	Gobj_Interactable::~Gobj_Interactable()
	{
	}
	void Gobj_Interactable::Initialize()
	{
		GameObject::Initialize();
	}
	void Gobj_Interactable::Update()
	{
		GameObject::Update();
	}
	void Gobj_Interactable::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Gobj_Interactable::Render()
	{
		GameObject::Render();
	}
}