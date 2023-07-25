#include "UI_Exit.h"

namespace sg
{
	UI_Exit::UI_Exit()
	{
		std::wstring name = Gobj_UI::GetName();
		name += L"_Exit";
		SetName(name);

		UI_Exit::Initialize();
	}
	UI_Exit::~UI_Exit()
	{
	}
	void UI_Exit::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		SetMaterial(L"UIExitButton");
		mTr->SetPosition(-188.5f, 97.5f, -0.1f);
		mMr->Initialize();

		SetOrder(1);

		Gobj_UI::Initialize();
	}
	void UI_Exit::Update()
	{
		Gobj_UI::Update();
	}
	void UI_Exit::LateUpdate()
	{
		Gobj_UI::LateUpdate();
	}
	void UI_Exit::Render()
	{
		Gobj_UI::Render();
	}
}