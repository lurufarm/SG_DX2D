#include "Img_LevUP.h"
#include "..\Engine_SOURCE\sgTime.h"

namespace sg
{
	Img_LevUP::Img_LevUP()
	{
		std::wstring name = Gobj_Img::GetName();
		name += L"_LevUp";
		SetName(name);
		Img_LevUP::Initialize();
	}
	Img_LevUP::~Img_LevUP()
	{
	}
	void Img_LevUP::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		SetMaterial(L"ImgLevUp");
		mMr->Initialize();
		mTime = 0.0f;
	}
	void Img_LevUP::Update()
	{
		mTime += Time::DeltaTime();

		Vector3 pos = mTr->GetPosition();
		pos.y += 20.0f * Time::DeltaTime();
		mTr->SetPosition(pos);

		if (mTime >= 1.5f)
			SetState(GameObject::eState::Dead);

		Gobj_Img::Update();
	}
	void Img_LevUP::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_LevUP::Render()
	{
		Gobj_Img::Render();
	}
}