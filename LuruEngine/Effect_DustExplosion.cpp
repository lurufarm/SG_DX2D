#include "Effect_DustExplosion.h"
#include "Effect_SmokePoison.h"

namespace sg
{
	Effect_DustExplosion::Effect_DustExplosion()
	{
		SetName(L"Effect_DustExplosion");
		Effect_DustExplosion::Initialize();
	}
	Effect_DustExplosion::~Effect_DustExplosion()
	{
	}
	void Effect_DustExplosion::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");
		mAtlas = Resources::Load<Texture>(L"Effect_DustExplosion", L"..\\Resources\\Effect\\dustexp.png");
		mAni->Create(L"Ani_Effect_DustExplotion", mAtlas, Vector2::Zero, Vector2(44.0f, 30.0f), 9, Vector2::Zero, 0.08f);
		mAni->PlayAnimation(L"Ani_Effect_DustExplotion", false, false);

		mMr->Initialize();

	}
	void Effect_DustExplosion::Update()
	{
		Gobj_Effect::Update();
		if (mAni->GetActiveAni()->IsComplete())
		{
			SetState(eState::Dead);
		}
	}
	void Effect_DustExplosion::LateUpdate()
	{
		Gobj_Effect::LateUpdate();
	}
	void Effect_DustExplosion::Render()
	{
		Gobj_Effect::Render();
	}
}