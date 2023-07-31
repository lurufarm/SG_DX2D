#include "UI_FocusBox.h"
#include "..\Engine_SOURCE\sgTime.h"
#include "SCRIPT_UI.h"
namespace sg
{
	UI_FocusBox::UI_FocusBox(int num)
	{
		mNum = num;

		std::wstring name = Gobj_UI::GetName();
		name += L"_FocusBox";
		SetName(name);

		UI_FocusBox::Initialize();

	}
	UI_FocusBox::~UI_FocusBox()
	{
	}
	void UI_FocusBox::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		switch (mNum)
		{
		case 0:
			SetMaterial(L"UISBox_tl");
			break;
		case 1:
			SetMaterial(L"UISBox_tr");
			break;
		case 2:
			SetMaterial(L"UISBox_bl");
			break;
		case 3:
			SetMaterial(L"UISBox_br");
			break;
		}

		mMr->Initialize();

		Gobj_UI::Initialize();
	}
	void UI_FocusBox::Update()
	{
		if (this->GetState() == Active)
			Gobj_UI::Update();
	}
	void UI_FocusBox::LateUpdate()
	{
		if (this->GetState() == Active)
			Gobj_UI::LateUpdate();
	}
	void UI_FocusBox::Render()
	{
		if (this->GetState() == Active)
			Gobj_UI::Render();
	}
}