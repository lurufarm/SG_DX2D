#include "Img_LevUp2.h"
#include "..\Engine_SOURCE\sgAnimator.h"
#include "..\Engine_SOURCE\sgLight.h"

#include "Gobj_Player.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	Img_LevUP2::Img_LevUP2()
	{
		std::wstring name = Gobj_Img::GetName();
		name += L"_LevUp2";
		SetName(name);
		Img_LevUP2::Initialize();
	}
	Img_LevUP2::~Img_LevUP2()
	{
	}
	void Img_LevUP2::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAni = AddComp<Animator>();

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"Img_LevUP2", L"..\\Resources\\Effect\\Evolution.png");

		mAni->Create(L"Ani_LevUP", atlas, Vector2::Zero, Vector2(26.0f, 45.0f), 17, Vector2::Zero, 0.05f);

		mAni->PlayAnimation(L"Ani_LevUP", false, true);
		mMr->Initialize();


		//mLg->SetType(eLightType::Point);
		//mLg->SetRadius(30.0f);
		//mLg->SetColor(Vector4(0.1f, 0.4f, 0.6f, 0.5f));

	}
	void Img_LevUP2::Update()
	{
		Vector3 pos = Player->GetComp<Transform>()->GetPosition();
		pos.y += 10.0f;
		mTr->SetPosition(pos);

		if (mAni->GetActiveAni()->IsComplete())
			SetState(GameObject::eState::Dead);

		Gobj_Img::Update();
	}
	void Img_LevUP2::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_LevUP2::Render()
	{
		Gobj_Img::Render();
	}
}