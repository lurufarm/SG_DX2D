#include "Effect_RockDust.h"

namespace sg
{
	Effect_RockDust::Effect_RockDust()
	{
		SetName(L"Effect_RockDust");
		Effect_RockDust::Initialize();
	}
	Effect_RockDust::~Effect_RockDust()
	{
	}
	void Effect_RockDust::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mAni = GetComp<Animator>();


		SetMesh();
		SetMaterial(L"AnimationMaterial");
		mAtlas = Resources::Load<Texture>(L"Effect_RockDust", L"..\\Resources\\Effect\\RockDust.png");
		mAni->Create(L"Ani_Effect_RockDust", mAtlas, Vector2::Zero, Vector2(50.0f, 51.0f), 6, Vector2::Zero, 0.1f);
		mAni->PlayAnimation(L"Ani_Effect_RockDust", false, false);

		//mTr->SetScale(0.5f, 0.5f, 1.0f);
		mMr->Initialize();

		//Light* mLight = AddComp<Light>();
		//mLight->SetType(eLightType::Point);
		//mLight->SetRadius(15.0f);
		//mLight->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

	}
	void Effect_RockDust::Update()
	{
		if (mAni->GetActiveAni()->IsComplete())
		{
			SetState(eState::Dead);
		}
		Gobj_Effect::Update();
	}
	void Effect_RockDust::LateUpdate()
	{
		Gobj_Effect::LateUpdate();
	}
	void Effect_RockDust::Render()
	{
		Gobj_Effect::Render();
	}
}