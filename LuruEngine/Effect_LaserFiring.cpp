#include "Effect_LaserFiring.h"

namespace sg
{
	Effect_LaserFiring::Effect_LaserFiring()
	{
		SetName(L"Effect_LaserFiring");
		Effect_LaserFiring::Initialize();

	}
	Effect_LaserFiring::~Effect_LaserFiring()
	{
	}
	void Effect_LaserFiring::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");
		mAtlas = Resources::Load<Texture>(L"Effect_LaserFiring", L"..\\Resources\\Effect\\LaserEffect.png");
		mAni->Create(L"Ani_Effect_LaserFiring", mAtlas, Vector2::Zero, Vector2(16.0f, 16.0f), 12, Vector2::Zero, 0.05f);
		mAni->PlayAnimation(L"Ani_Effect_LaserFiring", false, true);

		mMr->Initialize();
	}
	void Effect_LaserFiring::Update()
	{
		if (mAni->GetActiveAni()->IsComplete())
			SetState(eState::Dead);
		Gobj_Effect::Update();
	}
	void Effect_LaserFiring::LateUpdate()
	{
		Gobj_Effect::LateUpdate();
	}
	void Effect_LaserFiring::Render()
	{
		Gobj_Effect::Render();

	}
}