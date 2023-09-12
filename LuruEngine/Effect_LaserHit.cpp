#include "Effect_LaserHit.h"

namespace sg
{
	Effect_LaserHit::Effect_LaserHit()
	{
		SetName(L"Effect_LaserHit");
		Effect_LaserHit::Initialize();

	}
	Effect_LaserHit::~Effect_LaserHit()
	{
	}
	void Effect_LaserHit::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");
		mAtlas = Resources::Load<Texture>(L"Effect_LaserHit", L"..\\Resources\\Effect\\LaserEffect.png");
		mAni->Create(L"Ani_Effect_LaserHit", mAtlas, Vector2(0.0f, 16.0f), Vector2(16.0f, 16.0f), 5, Vector2::Zero, 0.1f);
		mAni->PlayAnimation(L"Ani_Effect_LaserHit", false, true);

		mMr->Initialize();
	}
	void Effect_LaserHit::Update()
	{
		if (mAni->GetActiveAni()->IsComplete())
			SetState(eState::Dead);
		Gobj_Effect::Update();
	}
	void Effect_LaserHit::LateUpdate()
	{
		Gobj_Effect::LateUpdate();
	}
	void Effect_LaserHit::Render()
	{
		Gobj_Effect::Render();

	}
}