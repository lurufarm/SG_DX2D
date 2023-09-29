#include "Effect_MobExplosion.h"

namespace sg
{
	Effect_MobExplosion::Effect_MobExplosion()
	{
		SetName(L"Effect_MobExplosion");
		Effect_MobExplosion::Initialize();
	}
	Effect_MobExplosion::~Effect_MobExplosion()
	{
	}
	void Effect_MobExplosion::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mAni = GetComp<Animator>();
		Collider2D* mCol = AddComp<Collider2D>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");
		mAtlas = Resources::Load<Texture>(L"Effect_MobExplosion", L"..\\Resources\\Effect\\BombExp1.png");
		mAni->Create(L"Ani_Effect_MobExplosion", mAtlas, Vector2::Zero, Vector2(46.0f, 30.0f), 8, Vector2::Zero, 0.05f);
		mAni->PlayAnimation(L"Ani_Effect_MobExplosion", false, false);

		mMr->Initialize();
	}
	void Effect_MobExplosion::Update()
	{
		if (mAni->GetActiveAni()->IsComplete())
			SetState(eState::Dead);
		Gobj_Effect::Update();
	}
	void Effect_MobExplosion::LateUpdate()
	{
		Gobj_Effect::LateUpdate();
	}
	void Effect_MobExplosion::Render()
	{
		Gobj_Effect::Render();
	}
}