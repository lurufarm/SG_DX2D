#include "Img_Torch.h"
#include "..\Engine_SOURCE\sgAnimator.h"
#include "..\Engine_SOURCE\sgLight.h"
namespace sg
{
	Img_Torch::Img_Torch()
	{
		SetName(L"Torch");

		Img_Torch::Initialize();
	}
	Img_Torch::~Img_Torch()
	{
	}
	void Img_Torch::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAni = AddComp<Animator>();

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"Img_Torch", L"..\\Resources\\Map\\torch.png");

		mAni->Create(L"Ani_Torch", atlas, Vector2::Zero, Vector2(14.0f, 32.0f), 6, Vector2::Zero, 0.1f);

		mMr->Initialize();

		mAni->PlayAnimation(L"Ani_Torch", true, true);

		mLg = AddComp<Light>();
		mLg->SetType(eLightType::Point);
		mLg->SetRadius(50.0f);
		mLg->SetColor(Vector4(0.6f, 0.5f, 0.4f, 0.5f));


	}
	void Img_Torch::Update()
	{
		Gobj_Img::Update();
	}
	void Img_Torch::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_Torch::Render()
	{
		Gobj_Img::Render();
	}
}