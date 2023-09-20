#include "UI_HPBase.h"
#include "Gobj_Player.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	UI_HPBase::UI_HPBase()
	{
		SetName(L"UI_HPBase");
		UI_HPBase::Initialize();
	}
	UI_HPBase::~UI_HPBase()
	{
	}
	void UI_HPBase::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		SetMaterial(L"UIHPBase");
		mMr->Initialize();
	}
	void UI_HPBase::Update()
	{
		Vector3 pos = Player->GetComp<Transform>()->GetPosition();
		pos.y += 20.0f;
		mTr->SetPosition(pos);
		Gobj_UI::Update();
	}
	void UI_HPBase::LateUpdate()
	{
		Gobj_UI::LateUpdate();
	}
	void UI_HPBase::Render()
	{
		Gobj_UI::Render();
	}
}