#include "Interact_LobbyCharacter.h"

namespace sg
{
	Interact_LobbyCharacter::Interact_LobbyCharacter()
	{
		std::wstring name = Gobj_Interactable::GetName();
		name += L"_LobbyCharacter";
		SetName(name);

		Interact_LobbyCharacter::Initialize();

	}
	Interact_LobbyCharacter::~Interact_LobbyCharacter()
	{
	}
	void Interact_LobbyCharacter::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		SetMaterial(L"InteractableLobbyCharacter");
		mMr->Initialize();

		Gobj_Interactable::Initialize();
	}
	void Interact_LobbyCharacter::Update()
	{
		Gobj_Interactable::Update();
	}
	void Interact_LobbyCharacter::LateUpdate()
	{
		Gobj_Interactable::LateUpdate();
	}
	void Interact_LobbyCharacter::Render()
	{
		Gobj_Interactable::Render();
	}
}