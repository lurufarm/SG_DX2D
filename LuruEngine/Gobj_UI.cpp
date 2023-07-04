#include "Gobj_UI.h"

namespace sg
{
	Gobj_UI::Gobj_UI()
		: mOrder(0)
	{
		SetName(L"Gobj_UI");
		AddComp<MeshRenderer>();
	}
	Gobj_UI::~Gobj_UI()
	{
	}
	void Gobj_UI::Initialize()
	{
		GameObject::Initialize();
	}
	void Gobj_UI::Update()
	{
		GameObject::Update();
	}
	void Gobj_UI::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Gobj_UI::Render()
	{
		GameObject::Render();
	}
}