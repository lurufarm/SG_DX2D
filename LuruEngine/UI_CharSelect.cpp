#include "UI_CharSelect.h"

#include "SCRIPT_UI.h"

namespace sg
{
	UI_CharSelect::UI_CharSelect()
	{
		std::wstring name = Gobj_UI::GetName();
		name += L"_CharSelect";
		SetName(name);

		UI_CharSelect::Initialize();
	}
	UI_CharSelect::~UI_CharSelect()
	{
	}
	void UI_CharSelect::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		SetMaterial(L"UICharSelect");
		mMr->Initialize();

		AddComp<SCRIPT_UI>();

	}
	void UI_CharSelect::Update()
	{
		Gobj_UI::Update();
	}
	void UI_CharSelect::LateUpdate()
	{
		Gobj_UI::LateUpdate();
	}
	void UI_CharSelect::Render()
	{
		Gobj_UI::Render();
	}
}