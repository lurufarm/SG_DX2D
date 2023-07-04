#include "Img_LobbyMap.h"

namespace sg
{
	Img_LobbyMap::Img_LobbyMap()
	{
		std::wstring name = Gobj_Img::GetName();
		name += L"_LobbyMap";
		SetName(name);

		Img_LobbyMap::Initialize();
	}
	Img_LobbyMap::~Img_LobbyMap()
	{
	}
	void Img_LobbyMap::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mTr->SetPosition(0.0f, 0.0f, 0.0f);
		SetMesh();
		SetMaterial(L"ImgLobbyMap");
		mMr->Initialize();
	}
	void Img_LobbyMap::Update()
	{
		Gobj_Img::Update();
	}
	void Img_LobbyMap::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_LobbyMap::Render()
	{
		Gobj_Img::Render();
	}
}