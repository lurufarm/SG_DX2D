#include "Img_Logo.h"

namespace sg
{
	Img_Logo::Img_Logo()
	{
		std::wstring name = Gobj_Img::GetName();
		name += L"_Logo";
		SetName(name);

		Img_Logo::Initialize();
	}
	Img_Logo::~Img_Logo()
	{
	}
	void Img_Logo::Initialize()
	{
		mTr = GetComp<Transform>();
		mTr->SetPosition(Vector3(-2.0f, -1.0f, 0.0f));
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		SetMaterial(L"ImgLogo01");
		mMr->Initialize();

		Gobj_Img::Initialize();
	}
	void Img_Logo::Update()
	{
		Gobj_Img::Update();
	}
	void Img_Logo::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_Logo::Render()
	{
		Gobj_Img::Render();
	}
}