#include "Effect_Hit.h"

namespace sg
{
	Effect_Hit::Effect_Hit()
	{
		SetName(L"Effect_Hit");
		Effect_Hit::Initialize();
	}
	Effect_Hit::~Effect_Hit()
	{
	}
	void Effect_Hit::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");
		mAtlas = Resources::Load<Texture>(L"Effect_Hit", L"..\\Resources\\Effect\\Hit1.png");
		mAni->Create(L"Ani_Effect_Hit", mAtlas, Vector2::Zero, Vector2(16.0f, 16.0f), 5, Vector2::Zero, 0.08f);
		mAni->PlayAnimation(L"Ani_Effect_Hit", false, false);

		mMr->Initialize();
	}
	void Effect_Hit::Update()
	{
		if (mAni->GetActiveAni()->IsComplete())
			SetState(eState::Dead);
		Gobj_Effect::Update();
	}
	void Effect_Hit::LateUpdate()
	{
		Gobj_Effect::LateUpdate();
	}
	void Effect_Hit::Render()
	{
		Gobj_Effect::Render();
	}
}