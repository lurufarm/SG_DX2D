#include "Img_Space1.h"

namespace sg
{
	Img_Space1::Img_Space1()
	{
		std::wstring name = Gobj_Img::GetName();
		name += L"_Space1";
		SetName(name);

		Img_Space1::Initialize();
	}
	Img_Space1::~Img_Space1()
	{
	}
	void Img_Space1::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mTr->SetPosition(0.0f, 0.0f, 2.0f);
		SetMesh();
		SetMaterial(L"ImgSpace1");
		mMr->Initialize();
	}
	void Img_Space1::Update()
	{
		Gobj_Img::Update();
	}
	void Img_Space1::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_Space1::Render()
	{
		Gobj_Img::Render();
	}
}