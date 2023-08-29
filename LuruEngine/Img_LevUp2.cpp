#include "Img_LevUp2.h"
#include "..\Engine_SOURCE\sgAnimator.h"
#include "..\Engine_SOURCE\sgLight.h"
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
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAni = AddComp<Animator>();
		mLg = AddComp<Light>();

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"Img_LevUP2", L"..\\Resources\\Effect\\Evolution.png");

		mAni->Create(L"Ani_LevUP", atlas, Vector2::Zero, Vector2(26.0f, 45.0f), 17, Vector2::Zero, 0.1f);

		mAni->PlayAnimation(L"Ani_LevUP", false, true);
		mMr->Initialize();


		//mLg->SetType(eLightType::Point);
		//mLg->SetRadius(30.0f);
		//mLg->SetColor(Vector4(0.1f, 0.4f, 0.6f, 0.5f));

	}
	void Img_LevUP2::Update()
	{
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