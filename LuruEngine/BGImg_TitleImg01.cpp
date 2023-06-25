#include "BGImg_TitleImg01.h"
#include "sgResources.h"

namespace sg
{
	TitleImg01::TitleImg01()
	{
		std::wstring name = Gobj_BGImg::GetName();
		name += L"_TitleImg01";
		SetName(name);

		//mTr = GetComp<Transform>();
		//mTr->SetPosition(Vector3(-2.0f, 0.0f, 0.0f));
		//mMr = GetComp<MeshRenderer>();
		//mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//mMr->SetMaterial(Resources::Find<Material>(L"BGImgTItle01"));

		TitleImg01::Initialize();
	}
	TitleImg01::~TitleImg01()
	{
	}
	void TitleImg01::Initialize()
	{
		mTr = GetComp<Transform>();
		mTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		mMr = GetComp<MeshRenderer>();
		//mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh")); 
		//mMr->SetMaterial(Resources::Find<Material>(L"BGImgTItle01"));
		SetMesh();
		SetMaterial(L"BGImgTItle01");
		Gobj_BGImg::Initialize();
	}
	void TitleImg01::Update()
	{
		Gobj_BGImg::Update();
	}
	void TitleImg01::LateUpdate()
	{
		Gobj_BGImg::LateUpdate();
	}
	void TitleImg01::Render()
	{
		Gobj_BGImg::Render();
	}
}