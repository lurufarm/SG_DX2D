#include "Effect_PoisionExplosion.h"

namespace sg
{
	Effect_PoisionExplosion::Effect_PoisionExplosion()
	{
		SetName(L"Effect_PoisionExplosion");
		Effect_PoisionExplosion::Initialize();
	}
	Effect_PoisionExplosion::~Effect_PoisionExplosion()
	{
	}
	void Effect_PoisionExplosion::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");
		mAtlas = Resources::Load<Texture>(L"Effect_PoisionExplosion", L"..\\Resources\\Effect\\PoisonExp.png");
		mAni->Create(L"Ani_Effect_PoisionExplosion", mAtlas, Vector2::Zero, Vector2(46.0f, 30.0f), 8, Vector2::Zero, 0.08f);
		mAni->PlayAnimation(L"Ani_Effect_PoisionExplosion", false, false);

		mMr->Initialize();

	}
	void Effect_PoisionExplosion::Update()
	{
		Gobj_Effect::Update();
		if (mAni->GetActiveAni()->IsComplete())
		{
			SetState(eState::Dead);
		}
	}
	void Effect_PoisionExplosion::LateUpdate()
	{
		Gobj_Effect::LateUpdate();
	}
	void Effect_PoisionExplosion::Render()
	{
		Gobj_Effect::Render();
	}
}