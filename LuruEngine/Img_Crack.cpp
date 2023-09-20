#include "Img_Crack.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
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

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"Img_Crack", L"..\\Resources\\Map\\Common\\Crack.png");

		mAni->Create(L"Ani_Crack_Normal", atlas, Vector2::Zero, Vector2(22.0f, 33.0f), 1, Vector2::Zero, 1.0f);
		mAni->Create(L"Ani_Crack_Lighting", atlas, Vector2(0.0f, 33.0f), Vector2(22.0f, 33.0f), 5, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Crack_Explosion", atlas, Vector2(0.0f, 66.0f), Vector2(22.0f, 33.0f), 14, Vector2::Zero, 0.05f);

		mMr->Initialize();

		mAni->PlayAnimation(L"Ani_Crack_Normal", true, true);

		//mLg->SetType(eLightType::Point);
		//mLg->SetRadius(30.0f);
		//mLg->SetColor(Vector4(0.1f, 0.4f, 0.6f, 0.5f));


	}
	void Img_Crack::Update()
	{
		std::vector<GameObject*> monsters = SceneManager::GetActiveScene()->GetLayer(eLayerType::Monster).GetGameObjects();

		if (monsters.size() > 0)
		{
			mAni->PlayAnimation(L"Ani_Crack_Lighting", true, true);
		}
		else
		{
			mAni->PlayAnimation(L"Ani_Crack_Explosion", false, true);
		}

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