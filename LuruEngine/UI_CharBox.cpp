#include "UI_CharBox.h"

namespace sg
{
	UI_CharBox::UI_CharBox()
	{
		UI_CharBox::Initialize();
	}
	UI_CharBox::~UI_CharBox()
	{
	}
	void UI_CharBox::Initialize()
	{
		mTr = GetComp<Transform>();
		mTr->SetScale(Vector3(17.0f, 17.0f, 1.0f));
		mCol = AddComp<Collider2D>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		SetMaterial(L"AnimationMaterial");
		mMr->SetImgScale(mTr->GetScale());
	}
	void UI_CharBox::Update()
	{
		Gobj_UI::Update();
	}
	void UI_CharBox::LateUpdate()
	{
		Gobj_UI::LateUpdate();
	}
	void UI_CharBox::Render()
	{
		//Gobj_UI::Render();
	}
}