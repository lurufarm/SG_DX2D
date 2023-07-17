#include "Interact_LobbyCardBook.h"

namespace sg
{
	Interact_LobbyCardBook::Interact_LobbyCardBook()
	{
		std::wstring name = Gobj_Interactable::GetName();
		name += L"_LobbyCardBook";
		SetName(name);

		Interact_LobbyCardBook::Initialize();
	}
	Interact_LobbyCardBook::~Interact_LobbyCardBook()
	{
	}
	void Interact_LobbyCardBook::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		SetMaterial(L"InteractableLobbyCardBook");
		mMr->Initialize();
	}
	void Interact_LobbyCardBook::Update()
	{
		Gobj_Interactable::Update();
	}
	void Interact_LobbyCardBook::LateUpdate()
	{
		Gobj_Interactable::LateUpdate();
	}
	void Interact_LobbyCardBook::Render()
	{
		Gobj_Interactable::Render();
	}
}