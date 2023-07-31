#include "Effect_Explosion.h"

namespace sg
{
	Effect_Explosion::Effect_Explosion()
	{
		SetName(L"Effect_Hit");
		Effect_Explosion::Initialize();
	}
	Effect_Explosion::~Effect_Explosion()
	{
	}
	void Effect_Explosion::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");
		mAtlas = Resources::Load<Texture>(L"Effect_Explosion", L"..\\Resources\\Effect\\BombExp1.png");
		mAni->Create(L"Ani_Effect_Explosion", mAtlas, Vector2::Zero, Vector2(46.0f, 30.0f), 8, Vector2::Zero, 0.05f);
		mAni->PlayAnimation(L"Ani_Effect_Explosion", false, false);

		mMr->Initialize();
	}
	void Effect_Explosion::Update()
	{
		if (mAni->GetActiveAni()->IsComplete())
			SetState(eState::Dead);
		Gobj_Effect::Update();
	}
	void Effect_Explosion::LateUpdate()
	{
		Gobj_Effect::LateUpdate();
	}
	void Effect_Explosion::Render()
	{
		Gobj_Effect::Render();
	}
}