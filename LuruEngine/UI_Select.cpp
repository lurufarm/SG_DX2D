#include "UI_Select.h"

namespace sg
{
	UI_Select::UI_Select(bool type)
		: mFocused(false)
	{
		mType = type;
		std::wstring name = Gobj_UI::GetName();

		if (type)
		{
			name += L"_Story";
			SetName(name);
		}
		else
		{
			name += L"_Party";
			SetName(name);
		}

		UI_Select::Initialize();

	}
	UI_Select::~UI_Select()
	{
	}
	void UI_Select::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();


		if (mType)
		{

			mTr->SetPosition(Vector3(-58.5, 0.0f, 0.0f));
			SetMaterial(L"ImgStory");
			SetOrder(2);
		}
		else
		{
			SetMesh();

			mTr->SetPosition(Vector3(58.5, 0.0f, 0.0f));
			SetMaterial(L"ImgParty");
			SetOrder(3);
		}

		mMr->Initialize();

		Gobj_UI::Initialize();
	}
	void UI_Select::Update()
	{
		Gobj_UI::Update();
	}
	void UI_Select::LateUpdate()
	{
		Gobj_UI::LateUpdate();
	}
	void UI_Select::Render()
	{
		Gobj_UI::Render();
	}
}
