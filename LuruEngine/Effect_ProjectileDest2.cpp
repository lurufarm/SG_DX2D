#include "Effect_ProjectileDest2.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "Effect_OldEntStem.h"

namespace sg
{
	Effect_ProjectileDest2::Effect_ProjectileDest2()
	{
		SetName(L"Effect_ProjectileDest2");
		Effect_ProjectileDest2::Initialize();
	}
	Effect_ProjectileDest2::~Effect_ProjectileDest2()
	{
	}
	void Effect_ProjectileDest2::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mAni = GetComp<Animator>();
		Collider2D* mCol = AddComp<Collider2D>();
		mCol->SetSize(Vector2(0.2f, 0.2f));

		SetMesh();
		SetMaterial(L"AnimationMaterial2");
		mAtlas = Resources::Load<Texture>(L"Effect_ProjectileDest2", L"..\\Resources\\Effect\\Crack.png");
		mAni->Create(L"Ani_Effect_ProjectileDest2", mAtlas, Vector2::Zero, Vector2(42.0f, 42.0f), 1, Vector2::Zero, 0.8f);
		mAni->PlayAnimation(L"Ani_Effect_ProjectileDest2", false, false);

		mTr->SetScale(0.5f, 0.5f, 1.0f);
		mMr->Initialize();

		//Light* mLight = AddComp<Light>();
		//mLight->SetType(eLightType::Point);
		//mLight->SetRadius(15.0f);
		//mLight->SetColor(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		mTime = 0.0f;
	}
	void Effect_ProjectileDest2::Update()
	{
		mTime += Time::DeltaTime();
		if (mTime >= 0.5f)
		{
			object::Instantiate<Effect_OldEntStem>(mTr->GetPosition(), eLayerType::Monster_Effect, SceneManager::GetActiveScene());
			SetState(eState::Dead);
		}
		Gobj_Effect::Update();
	}
	void Effect_ProjectileDest2::LateUpdate()
	{
		Gobj_Effect::LateUpdate();
	}
	void Effect_ProjectileDest2::Render()
	{
		Gobj_Effect::Render();
	}
}