#include "Interact_LobbyGate.h"
#include "sgAnimator.h"
#include "SCRIPT_Gate.h"

namespace sg
{
	Interact_LobbyGate::Interact_LobbyGate()
	{
		std::wstring name = Gobj_Interactable::GetName();
		name += L"_LobbyGate";
		SetName(name);

		Interact_LobbyGate::Initialize();
	}
	Interact_LobbyGate::~Interact_LobbyGate()
	{


	}
	void Interact_LobbyGate::Initialize()
	{
		mTr = GetComp<Transform>();
		//mTr->SetPosition(0.0f, 10.0f, 0.0f);
		//mTr->SetScale(50.0f, 59.0f, 1.0f);
		mMr = GetComp<MeshRenderer>();
		
		mAni = AddComp<Animator>();
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"Lobby_Gate", L"..\\Resources\\Lobby\\SurvivalBd1.png");
		mAni->Create(L"LobbyGate", atlas, Vector2::Zero, Vector2(50.0f, 59.0f), 5, Vector2::Zero, 0.1f);
		mAni->PlayAnimation(L"LobbyGate", true, true);

		SetMesh();
		SetMaterial(L"AnimationMaterial");
		mMr->Initialize();

		mCol = GetComp<Collider2D>();
		//mCol->SetSize(Vector2(0.5f, 0.3f));

		AddComp<SCRIPT_Gate>();

	}
	void Interact_LobbyGate::Update()
	{
		Gobj_Interactable::Update();
	}
	void Interact_LobbyGate::LateUpdate()
	{
		Gobj_Interactable::LateUpdate();
	}
	void Interact_LobbyGate::Render()
	{
		Gobj_Interactable::Render();
	}
}