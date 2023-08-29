#include "Img_StartingPlate.h"

namespace sg
{
	Img_StartingPlate::Img_StartingPlate()
	{
		std::wstring name = Gobj_Img::GetName();
		name += L"_StartingPlate";
		SetName(name);
		Img_StartingPlate::Initialize();
	}
	Img_StartingPlate::~Img_StartingPlate()
	{
	}
	void Img_StartingPlate::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		SetMaterial(L"ImgStartingPlate");
		mMr->Initialize();
	}
	void Img_StartingPlate::Update()
	{
		Gobj_Img::Update();
	}
	void Img_StartingPlate::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_StartingPlate::Render()
	{
		Gobj_Img::Render();
	}
}