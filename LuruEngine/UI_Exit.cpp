#include "UI_Exit.h"
#include "sgSelectScript.h"

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
		mTr->SetPosition(-2.9f, 1.5f, -1.0f);
		mMr->Initialize();

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