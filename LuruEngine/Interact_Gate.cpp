#include "Interact_Gate.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgAnimator.h"
#include "SCRIPT_Gate.h"

namespace sg
{
	Interact_Gate::Interact_Gate(int num)
		: mAni(nullptr)
	{
		mGateType = num;
		mOpen = false;
		Interact_Gate::Initialize();
	}
	Interact_Gate::~Interact_Gate()
	{
	}
	void Interact_Gate::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mAni = AddComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		std::shared_ptr<Texture> atlas0 = Resources::Load<Texture>(L"Nor_Gate", L"..\\Resources\\Map\\Common\\NorGate.png");
		std::shared_ptr<Texture> atlas1 = Resources::Load<Texture>(L"Boss_Gate", L"..\\Resources\\Map\\Common\\BossGate.png");
		mAni->Create(L"Nor_Gate_Closed", atlas0, Vector2::Zero, Vector2(30.0f, 24.0f), 1, Vector2::Zero, 1.0f);
		//mAni->Create(L"Nor_Gate_Opened", atlas0, Vector2(0.0f, 24.0f), Vector2(30.0f, 24.0f), 1, Vector2::Zero, 1.0f);
		mAni->Create(L"Boss_Gate_Closed", atlas1, Vector2::Zero, Vector2(30.0f, 24.0f), 1, Vector2::Zero, 1.0f);
		//mAni->Create(L"Boss_Gate_Opened", atlas1, Vector2(0.0f, 24.0f), Vector2(30.0f, 24.0f), 1, Vector2::Zero, 1.0f);

		//AddComp<SCRIPT_Gate>();

		switch (mGateType)
		{
		case 0:
			SetName(L"Nor_Gate");
			mAni->PlayAnimation(L"Nor_Gate_Closed", true, true);
			break;
		case 1:
			SetName(L"Boss_Gate");
			mAni->PlayAnimation(L"Boss_Gate_Closed", true, true);
			break;
		}

		mMr->Initialize();
		mCol = GetComp<Collider2D>();
		mOpen = false;
		SetSelected(false);
	}
	void Interact_Gate::Update()
	{
		if (this->GetSelected() && Input::KeyD(eKeyCode::ENTER) && mOpen)
		{
			SceneManager::LoadNextScene();
		}
		Gobj_Interactable::Update();
	}
	void Interact_Gate::LateUpdate()
	{
		Gobj_Interactable::LateUpdate();
	}
	void Interact_Gate::Render()
	{
		Gobj_Interactable::Render();
	}
}