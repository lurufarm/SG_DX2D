#include "Bullet_GreenOrb.h"
#include "SCRIPT_MobProjectile.h"
#include "Bullet_BigGreenOrb.h"

namespace sg
{
	Bullet_GreenOrb::Bullet_GreenOrb(Gobj_Monster* BulletOwner)
	{
		SetName(L"GreenOrb");
		this->SetProjOwner(BulletOwner);
		mProjOwner = BulletOwner;
		mFirstPos = mProjOwner->GetComp<Transform>()->GetPosition();
		mType = eMProjType::Basic_RandDir;
		Bullet_GreenOrb::Initialize();
	}
	Bullet_GreenOrb::Bullet_GreenOrb(Vector2 dir, Bullet_BigGreenOrb* BOrb)
	{
		SetName(L"GreenOrb");
		mBOrb = BOrb;
		mFirstPos = mBOrb->GetComp<Transform>()->GetPosition();
		mType = eMProjType::Basic_Dir;
		mLastPos = Vector3(dir.x, dir.y, 0.0f);

		Bullet_GreenOrb::Initialize();
	}
	Bullet_GreenOrb::~Bullet_GreenOrb()
	{
	}
	void Bullet_GreenOrb::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		mAni = AddComp<Animator>();
		mCol = GetComp<Collider2D>();
		mCol->SetSize(Vector2(0.9f, 0.9f));
		SetMesh();
		SetMaterial(L"AnimationMaterial");
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"GreenOrb", L"..\\Resources\\Monster\\Bosses\\OrbGreen1.png");
		mAni->Create(L"Ani_GreenOrb", atlas, Vector2::Zero, Vector2(8.0f, 8.0f), 4, Vector2::Zero, 0.05f);
		mMr->Initialize();
		mAni->PlayAnimation(L"Ani_GreenOrb", true, true);
		AddComp<SCRIPT_MobProjectile>();

	}
	void Bullet_GreenOrb::Update()
	{		
		Gobj_MobProjectile::Update();
	}
	void Bullet_GreenOrb::LateUpdate()
	{
		Gobj_MobProjectile::LateUpdate();
	}
	void Bullet_GreenOrb::Render()
	{
		Gobj_MobProjectile::Render();
	}
}