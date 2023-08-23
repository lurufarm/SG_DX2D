#include "Img_Crack.h"
#include "..\Engine_SOURCE\sgAnimator.h"
#include "..\Engine_SOURCE\sgLight.h"
namespace sg
{
	Img_Crack::Img_Crack()
	{
		std::wstring name = Gobj_Img::GetName();
		name += L"_Crack";
		SetName(name);

		Img_Crack::Initialize();
	}
	Img_Crack::~Img_Crack()
	{
	}
	void Img_Crack::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAni = AddComp<Animator>();
		mLg = AddComp<Light>();

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"Img_LobbyTorch", L"..\\Resources\\Lobby\\LobbyTorch.png");

		mAni->Create(L"Ani_LobbyTorch", atlas, Vector2::Zero, Vector2(12.0f, 31.0f), 6, Vector2::Zero, 0.1f);

		mMr->Initialize();

		mAni->PlayAnimation(L"Ani_LobbyTorch", true, true);

		mLg->SetType(eLightType::Point);
		mLg->SetRadius(30.0f);
		mLg->SetColor(Vector4(0.1f, 0.4f, 0.6f, 0.5f));


	}
	void Img_Crack::Update()
	{
		Gobj_Img::Update();
	}
	void Img_Crack::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_Crack::Render()
	{
		Gobj_Img::Render();
	}
}