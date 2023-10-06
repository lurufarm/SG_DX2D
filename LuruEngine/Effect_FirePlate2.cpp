#include "Effect_FirePlate2.h"
#include "Effect_FirePlate.h"

namespace sg
{
	Effect_FirePlate2::Effect_FirePlate2()
	{
		SetName(L"Effect_FirePlate2");
		Effect_FirePlate2::Initialize();
	}
	Effect_FirePlate2::~Effect_FirePlate2()
	{
	}
	void Effect_FirePlate2::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = AddComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Load<Texture>(L"Effect_FirePlate2", L"..\\Resources\\Effect\\fireplate2.png");
		mAni->Create(L"Ani_Effect_FirePlate2", mAtlas, Vector2::Zero, Vector2(32.0f, 25.0f), 7, Vector2::Zero, 0.2f);
		mAni->PlayAnimation(L"Ani_Effect_FirePlate2", false, true);

		mMr->Initialize();

	}
	void Effect_FirePlate2::Update()
	{
		if (mAni->GetActiveAni()->IsComplete())
			this->SetState(Dead);

		Gobj_Effect::Update();
	}
	void Effect_FirePlate2::LateUpdate()
	{
		Gobj_Effect::LateUpdate();
	}
	void Effect_FirePlate2::Render()
	{
		Gobj_Effect::Render();
	}
}