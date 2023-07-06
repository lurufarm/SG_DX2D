#include "Img_TitleImg01.h"

namespace sg
{
	Img_Title::Img_Title()
	{
		std::wstring name = Gobj_Img::GetName();
		name += L"_Title";
		SetName(name);

		Img_Title::Initialize();
	}
	Img_Title::~Img_Title()
	{
	}
	void Img_Title::Initialize()
	{
		mTr = GetComp<Transform>();
		mTr->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		SetMaterial(L"ImgTitle01");
		mMr->Initialize();

		Gobj_Img::Initialize();
	}
	void Img_Title::Update()
	{
		Gobj_Img::Update();
	}
	void Img_Title::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_Title::Render()
	{
		Gobj_Img::Render();
	}
}