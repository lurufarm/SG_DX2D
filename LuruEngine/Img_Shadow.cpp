#include "Img_Shadow.h"

namespace sg
{
	Img_Shadow::Img_Shadow()
	{
		SetName(L"Img_Shadow");
		Img_Shadow::Initialize();
	}
	Img_Shadow::~Img_Shadow()
	{
	}
	void Img_Shadow::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		SetMaterial(L"ImgShadow");
		mMr->Initialize();
		SetTransParent(true);
	}
	void Img_Shadow::Update()
	{
		Gobj_Img::Update();
	}
	void Img_Shadow::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_Shadow::Render()
	{
		Gobj_Img::Render();
	}
}