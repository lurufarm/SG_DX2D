#include "Effect_SmokePoison.h"

namespace sg
{
	Effect_SmokePoison::Effect_SmokePoison()
	{
		SetName(L"Effect_SmokePoison");
		Effect_SmokePoison::Initialize();
	}
	Effect_SmokePoison::~Effect_SmokePoison()
	{
	}
	void Effect_SmokePoison::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");
		mAtlas = Resources::Load<Texture>(L"Effect_SmokePoison", L"..\\Resources\\Effect\\SmokePoison.png");
		mAni->Create(L"Ani_Effect_SmokePoison", mAtlas, Vector2::Zero, Vector2(38.0f, 19.0f), 8, Vector2::Zero, 0.08f);
		mAni->PlayAnimation(L"Ani_Effect_SmokePoison", false, false);

		mMr->Initialize();

	}
	void Effect_SmokePoison::Update()
	{
		Gobj_Effect::Update();
		if (mAni->GetActiveAni()->IsComplete())
		{
			SetState(eState::Dead);
		}
	}
	void Effect_SmokePoison::LateUpdate()
	{
		Gobj_Effect::LateUpdate();
	}
	void Effect_SmokePoison::Render()
	{
		Gobj_Effect::Render();
	}
}