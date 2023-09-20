#include "Effect_OldEntStem.h"

namespace sg
{
	Effect_OldEntStem::Effect_OldEntStem()
	{
		SetName(L"Effect_OldEntStem");
		Effect_OldEntStem::Initialize();
	}
	Effect_OldEntStem::~Effect_OldEntStem()
	{
	}
	void Effect_OldEntStem::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mAni = GetComp<Animator>();
		Collider2D* mCol = AddComp<Collider2D>();
		SetMesh();
		SetMaterial(L"AnimationMaterial");
		mAtlas = Resources::Load<Texture>(L"Effect_OldEntStem", L"..\\Resources\\Monster\\bosses\\OldEntStem.png");
		mAni->Create(L"Ani_Effect_OldEntStem", mAtlas, Vector2::Zero, Vector2(16.0f, 27.0f), 6, Vector2::Zero, 0.08f);
		mAni->PlayAnimation(L"Ani_Effect_OldEntStem", false, true);

		mMr->Initialize();
		mCol->SetCenter(Vector2(0.0f, -8.0f));
		mCol->SetSize(Vector2(0.2f, 0.4f));

	}
	void Effect_OldEntStem::Update()
	{
		if (mAni->GetActiveAni()->IsComplete())
		{
			SetState(eState::Dead);
		}
		Gobj_Effect::Update();
	}
	void Effect_OldEntStem::LateUpdate()
	{
		Gobj_Effect::LateUpdate();
	}
	void Effect_OldEntStem::Render()
	{
		Gobj_Effect::Render();
	}
}