#include "Effect_ProjectileDest.h"

namespace sg
{
	Effect_ProjectileDest::Effect_ProjectileDest()
	{
		SetName(L"Effect_ProjectileDest");
		Effect_ProjectileDest::Initialize();
	}
	Effect_ProjectileDest::~Effect_ProjectileDest()
	{
	}
	void Effect_ProjectileDest::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mAni = GetComp<Animator>(); 
		Collider2D* mCol = AddComp<Collider2D>();
		mCol->SetSize(Vector2(0.2f, 0.2f));

		SetMesh();
		SetMaterial(L"AnimationMaterial2");
		mAtlas = Resources::Load<Texture>(L"Effect_ProjectileDest", L"..\\Resources\\Effect\\Crack.png");
		mAni->Create(L"Ani_Effect_ProjectileDest", mAtlas, Vector2::Zero, Vector2(42.0f, 42.0f), 1, Vector2::Zero, 1.0f);
		mAni->PlayAnimation(L"Ani_Effect_ProjectileDest", false, false);

		mTr->SetScale(0.5f, 0.5f, 1.0f);
		mMr->Initialize();

		//Light* mLight = AddComp<Light>();
		//mLight->SetType(eLightType::Point);
		//mLight->SetRadius(15.0f);
		//mLight->SetColor(Vector4(1.0f, 0.0f, 0.0f, 1.0f));

	}
	void Effect_ProjectileDest::Update()
	{
		if (mAni->GetActiveAni()->IsComplete())
		{
			SetState(eState::Dead);
		}
		Gobj_Effect::Update();
	}
	void Effect_ProjectileDest::LateUpdate()
	{
		Gobj_Effect::LateUpdate();
	}
	void Effect_ProjectileDest::Render()
	{
		Gobj_Effect::Render();
	}
}