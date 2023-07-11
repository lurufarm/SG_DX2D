#include "Img_LobbyMolding.h"

namespace sg
{
	Img_LobbyMolding::Img_LobbyMolding()
	{
		std::wstring name = Gobj_Img::GetName();
		name += L"_LobbyMolding";
		SetName(name);

		Img_LobbyMolding::Initialize();
	}
	Img_LobbyMolding::~Img_LobbyMolding()
	{
	}
	void Img_LobbyMolding::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		SetMaterial(L"ImgMolding");
		mMr->Initialize();

		Gobj_Img::Initialize();
	}
	void Img_LobbyMolding::Update()
	{
		Gobj_Img::Update();
	}
	void Img_LobbyMolding::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_LobbyMolding::Render()
	{
		Gobj_Img::Render();
	}
}