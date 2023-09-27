#include "Effect_BigDust.h"

namespace sg
{
	Effect_BigDust::Effect_BigDust()
	{
		SetName(L"Effect_BigDust");
		Effect_BigDust::Initialize();
	}
	Effect_BigDust::~Effect_BigDust()
	{
	}
	void Effect_BigDust::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");
		mAtlas = Resources::Load<Texture>(L"Effect_BigDust", L"..\\Resources\\Effect\\BigDust.png");
		mAni->Create(L"Ani_Effect_BigDust", mAtlas, Vector2::Zero, Vector2(103.0f, 48.0f), 11, Vector2::Zero, 0.1f);
		mAni->PlayAnimation(L"Ani_Effect_BigDust", false, false);

		mMr->Initialize();

	}
	void Effect_BigDust::Update()
	{
		Gobj_Effect::Update();
		if (mAni->GetActiveAni()->IsComplete())
		{
			SetState(eState::Dead);
		}
	}
	void Effect_BigDust::LateUpdate()
	{
		Gobj_Effect::LateUpdate();
	}
	void Effect_BigDust::Render()
	{
		Gobj_Effect::Render();
	}
}