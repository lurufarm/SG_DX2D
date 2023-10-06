#include "Bullet_PoisonOrb.h"
#include "SCRIPT_MobProjectile.h"

namespace sg
{
	Bullet_PoisonOrb::Bullet_PoisonOrb(Gobj_Monster* BulletOwner)
	{
		SetName(L"PoisonOrb");
		this->SetProjOwner(BulletOwner);
		mProjOwner = BulletOwner;
		mFirstPos = mProjOwner->GetComp<Transform>()->GetPosition();
		mType = eMProjType::PoisonOrb;

		Bullet_PoisonOrb::Initialize();
	}
	Bullet_PoisonOrb::Bullet_PoisonOrb(Gobj_Monster* BulletOwner, Vector3 dir)
	{
		SetName(L"PoisonOrb");
		this->SetProjOwner(BulletOwner);
		mProjOwner = BulletOwner;
		mFirstPos = mProjOwner->GetComp<Transform>()->GetPosition();
		mType = eMProjType::Basic_Dir;
		mLastPos = dir;

		Bullet_PoisonOrb::Initialize();
	}
	Bullet_PoisonOrb::~Bullet_PoisonOrb()
	{
		int a = 0;
	}
	void Bullet_PoisonOrb::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		mAni = AddComp<Animator>();
		mCol = GetComp<Collider2D>();
		SetMesh();
		SetMaterial(L"AnimationMaterial");

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"PoisonOrb", L"..\\Resources\\Monster\\PoisonOrb.png");
		mAni->Create(L"Ani_PoisonOrb", atlas, Vector2::Zero, Vector2(8.0f, 8.0f), 4, Vector2::Zero, 0.05f);
		mMr->Initialize();
		mAni->PlayAnimation(L"Ani_PoisonOrb", true, true);

		mCol->SetSize(Vector2(0.8f, 0.8f));
		AddComp<SCRIPT_MobProjectile>();
	}
	void Bullet_PoisonOrb::Update()
	{
		Gobj_MobProjectile::Update();
	}
	void Bullet_PoisonOrb::LateUpdate()
	{
		Gobj_MobProjectile::LateUpdate();
	}
	void Bullet_PoisonOrb::Render()
	{
		Gobj_MobProjectile::Render();
	}
}