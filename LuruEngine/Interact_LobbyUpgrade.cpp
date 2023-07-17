#include "Interact_LobbyUpgrade.h"

namespace sg
{
	Interact_LobbyUpgrade::Interact_LobbyUpgrade()
	{
		std::wstring name = Gobj_Interactable::GetName();
		name += L"_LobbyUpgrade";
		SetName(name);

		Interact_LobbyUpgrade::Initialize();
	}
	Interact_LobbyUpgrade::~Interact_LobbyUpgrade()
	{
	}
	void Interact_LobbyUpgrade::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		SetMaterial(L"InteractableLobbyUpgrade");
		mMr->Initialize();

		SetOrder(2);
		
		Gobj_Interactable::Initialize();
	}
	void Interact_LobbyUpgrade::Update()
	{
		Gobj_Interactable::Update();
	}
	void Interact_LobbyUpgrade::LateUpdate()
	{
		Gobj_Interactable::LateUpdate();
	}
	void Interact_LobbyUpgrade::Render()
	{
		Gobj_Interactable::Render();
	}
}