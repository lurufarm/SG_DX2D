#include "Img_CatPattern.h"
#include "..\Engine_SOURCE\sgTime.h"

namespace sg
{
	Img_CatPattern::Img_CatPattern()
	{
		std::wstring name = Gobj_Img::GetName();
		name += L"_CatPattern";
		SetName(name);

		Img_CatPattern::Initialize();
	}
	Img_CatPattern::~Img_CatPattern()
	{
	}
	void Img_CatPattern::Initialize()
	{
		mTr = GetComp<Transform>();
		mTr->SetPosition(0.0f, 0.0f, 0.1f);
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		SetMaterial(L"ImgCatPattern");
		mMr->Initialize();
	}
	void Img_CatPattern::Update()
	{
		Gobj_Img::Update();
	}
	void Img_CatPattern::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_CatPattern::Render()
	{
		Gobj_Img::Render();
	}
}