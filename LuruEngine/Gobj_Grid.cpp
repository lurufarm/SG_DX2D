#include "Gobj_Grid.h"
#include "SCRIPT_GridScript.h"

namespace sg
{
	Gobj_Grid::Gobj_Grid()
	{
		SetName(L"Grid");
		Gobj_Grid::Initialize();
	}
	Gobj_Grid::~Gobj_Grid()
	{
	}
	void Gobj_Grid::Initialize()
	{
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mMr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));

		GameObject::Initialize();
	}
	void Gobj_Grid::Update()
	{
		GameObject::Update();
	}
	void Gobj_Grid::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Gobj_Grid::Render()
	{
		GameObject::Render();
	}
}