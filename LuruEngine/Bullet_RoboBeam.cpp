#include "Bullet_RoboBeam.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "SCRIPT_Bullet.h"

namespace sg
{
	Bullet_RoboBeam::Bullet_RoboBeam()
	{
		SetName(L"RoboBeam");
		Bullet_RoboBeam::Initialize();
	}
	Bullet_RoboBeam::Bullet_RoboBeam(int num)
	{
		SetName(L"RoboBeam");
		mThisNum = num;
		Bullet_RoboBeam::Initialize();
	}
	Bullet_RoboBeam::~Bullet_RoboBeam()
	{
	}
	void Bullet_RoboBeam::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		mAni = AddComp<Animator>();
		mCol = GetComp<Collider2D>();
		mType = eBulletType::Robo;
		mBulletOwner = SceneManager::GetChar(L"Robo");
		SetMesh();
		SetMaterial(L"AnimationMaterial");

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"RoboBeam", L"..\\Resources\\Character\\Robo\\RoboBeam.png");
		mAni->Create(L"Ani_RoboBeam0", atlas, Vector2(0.0f, 0.0f), Vector2(42.0f, 32.0f), 14, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_RoboBeam1", atlas, Vector2(0.0f, 32.0f), Vector2(42.0f, 32.0f), 14, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_RoboBeam2", atlas, Vector2(0.0f, 64.0f), Vector2(42.0f, 32.0f), 14, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_RoboBeam3", atlas, Vector2(0.0f, 96.0f), Vector2(42.0f, 32.0f), 14, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_RoboBeam4", atlas, Vector2(0.0f, 128.0f), Vector2(42.0f, 32.0f), 14, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_RoboBeam5", atlas, Vector2(0.0f, 160.0f), Vector2(42.0f, 32.0f), 14, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_RoboBeam6", atlas, Vector2(0.0f, 192.0f), Vector2(42.0f, 32.0f), 14, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_RoboBeam7", atlas, Vector2(0.0f, 224.0f), Vector2(42.0f, 32.0f), 14, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_RoboBeam8", atlas, Vector2(0.0f, 256.0f), Vector2(42.0f, 32.0f), 14, Vector2::Zero, 0.05f);
		
		mTr->SetScale(Vector3(1.0f, 10.0f, 1.0f));
		mMr->Initialize();
		//Vector3 BOpos = mBulletOwner->GetComp<Transform>()->GetPosition();
		//Vector3 BOTpos = mBulletOwner->GetTarget()->GetComp<Transform>()->GetPosition();
		//mCol->SetSize(Vector2(1.0f, 10.0f));

		switch (mThisNum)
		{
		case 0:
			mAni->PlayAnimation(L"Ani_RoboBeam0", false, true);
			break;
		case 1:
			mAni->PlayAnimation(L"Ani_RoboBeam1", false, true);
			break;
		case 2:
			mAni->PlayAnimation(L"Ani_RoboBeam2", false, true);
			break;
		case 3:
			mAni->PlayAnimation(L"Ani_RoboBeam3", false, true);
			break;
		case 4:
			mAni->PlayAnimation(L"Ani_RoboBeam4", false, true);
			break;
		case 5:
			mAni->PlayAnimation(L"Ani_RoboBeam5", false, true);
			break;
		case 6:
			mAni->PlayAnimation(L"Ani_RoboBeam6", false, true);
			break;
		case 7:
			mAni->PlayAnimation(L"Ani_RoboBeam7", false, true);
			break;
		case 8:
			mAni->PlayAnimation(L"Ani_RoboBeam8", false, true);
			break;
		default:
			mAni->PlayAnimation(L"Ani_RoboBeam8", false, true);
			break;
		}

		Gobj_Bullet::Initialize();

		AddComp<SCRIPT_Bullet>();
	}
	void Bullet_RoboBeam::Update()
	{
		if (mAni->GetActiveAni()->IsComplete())
			SetState(GameObject::eState::Dead);

		if (mAni->GetActiveAni()->GetAniIndex() > 5 && mAni->GetActiveAni()->GetAniIndex() < 9)
		{
		
			if (mAni->GetActiveAni()->GetKey() == L"Ani_RoboBeam0")
				mCol->SetSize(Vector2(CalculatePercent(42, 10),1.0f));
			else if (mAni->GetActiveAni()->GetKey() == L"Ani_RoboBeam1")
				mCol->SetSize(Vector2(CalculatePercent(42, 14), 1.0f));
			else if (mAni->GetActiveAni()->GetKey() == L"Ani_RoboBeam2")
				mCol->SetSize(Vector2(CalculatePercent(42, 18), 1.0f));
			else if (mAni->GetActiveAni()->GetKey() == L"Ani_RoboBeam3")
				mCol->SetSize(Vector2(CalculatePercent(42, 22), 1.0f));
			else if (mAni->GetActiveAni()->GetKey() == L"Ani_RoboBeam4")
				mCol->SetSize(Vector2(CalculatePercent(42, 26), 1.0f));
			else if (mAni->GetActiveAni()->GetKey() == L"Ani_RoboBeam5")
				mCol->SetSize(Vector2(CalculatePercent(42, 30), 1.0f));
			else if (mAni->GetActiveAni()->GetKey() == L"Ani_RoboBeam6")
				mCol->SetSize(Vector2(CalculatePercent(42, 34), 1.0f));
			else if (mAni->GetActiveAni()->GetKey() == L"Ani_RoboBeam7")
				mCol->SetSize(Vector2(CalculatePercent(42, 38), 1.0f));
			else if (mAni->GetActiveAni()->GetKey() == L"Ani_RoboBeam8")
				mCol->SetSize(Vector2(1.0f, 1.0f));
		}
		else
			mCol->SetSize(Vector2(0.0f, 0.0f));

		Gobj_Bullet::Update();
	}
	void Bullet_RoboBeam::LateUpdate()
	{
		Gobj_Bullet::LateUpdate();
	}
	void Bullet_RoboBeam::Render()
	{
		Gobj_Bullet::Render();
	}
}