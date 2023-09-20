#include "Effect_FirePlate.h"

namespace sg
{
	Effect_FirePlate::Effect_FirePlate()
	{
		SetName(L"Effect_FirePlate");
		Effect_FirePlate::Initialize();
	}
	Effect_FirePlate::~Effect_FirePlate()
	{
	}
	void Effect_FirePlate::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = AddComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Load<Texture>(L"Effect_FirePlate", L"..\\Resources\\Effect\\fireplate.png");
		mAni->Create(L"Ani_Effect_FirePlate", mAtlas, Vector2::Zero, Vector2(23.0f, 11.0f), 7, Vector2::Zero, 0.2f);
		mAni->PlayAnimation(L"Ani_Effect_FirePlate", false, true);

		mMr->Initialize();

	}
	void Effect_FirePlate::Update()
	{
		if (mAni->GetActiveAni()->IsComplete())
			this->SetState(Dead);

		Gobj_Effect::Update();
	}
	void Effect_FirePlate::LateUpdate()
	{
		Gobj_Effect::LateUpdate();
	}
	void Effect_FirePlate::Render()
	{
		Gobj_Effect::Render();
	}
}