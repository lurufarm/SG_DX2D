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
	Bullet_RoboBeam::~Bullet_RoboBeam()
	{
	}
	void Bullet_RoboBeam::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		mAni = AddComp<Animator>();
		mCol = GetComp<Collider2D>();
		mType = eBulletType::Robo;
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
		//mAni->PlayAnimation(L"Ani_RoboBeam0", false, true);

		mCol->SetSize(Vector2(1.0f, 10.0f));

		mBulletOwner = SceneManager::GetChar(L"Robo");
		Gobj_Bullet::Initialize();

		AddComp<SCRIPT_Bullet>();
	}
	void Bullet_RoboBeam::Update()
	{
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