#include "Img_Space2.h"

namespace sg
{
	Img_Space2::Img_Space2()
	{
		std::wstring name = Gobj_Img::GetName();
		name += L"_Space2";
		SetName(name);

		Img_Space2::Initialize();
	}
	Img_Space2::~Img_Space2()
	{
	}
	void Img_Space2::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mTr->SetPosition(0.0f, 0.0f, 9.0f);
		SetMesh();
		SetMaterial(L"ImgSpace2");
		mMr->Initialize();
	}
	void Img_Space2::Update()
	{
		Gobj_Img::Update();
	}
	void Img_Space2::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_Space2::Render()
	{
		Gobj_Img::Render();
	}
}