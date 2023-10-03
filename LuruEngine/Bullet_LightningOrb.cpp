#include "Bullet_LightningOrb.h"
#include "SCRIPT_MobProjectile.h"

namespace sg
{
	Bullet_LightningOrb::Bullet_LightningOrb(Gobj_Monster* BulletOwner)
	{
		SetName(L"LightningOrb");
		this->SetProjOwner(BulletOwner);
		mProjOwner = BulletOwner;
		mFirstPos = mProjOwner->GetComp<Transform>()->GetPosition();
		Bullet_LightningOrb::Initialize();
	}
	Bullet_LightningOrb::~Bullet_LightningOrb()
	{
	}
	void Bullet_LightningOrb::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		mAni = AddComp<Animator>();
		mCol = GetComp<Collider2D>();
		mType = eMProjType::LightningOrb;
		SetMesh();
		SetMaterial(L"AnimationMaterial");

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"LightningOrb", L"..\\Resources\\Monster\\PoisonOrb.png");
		mAni->Create(L"Ani_LightningOrb", atlas, Vector2::Zero, Vector2(8.0f, 8.0f), 4, Vector2::Zero, 0.05f);
		mMr->Initialize();
		mAni->PlayAnimation(L"Ani_LightningOrb", true, true);

		AddComp<SCRIPT_MobProjectile>();
	}
	void Bullet_LightningOrb::Update()
	{
		Gobj_MobProjectile::Update();
	}
	void Bullet_LightningOrb::LateUpdate()
	{
		Gobj_MobProjectile::LateUpdate();
	}
	void Bullet_LightningOrb::Render()
	{
		Gobj_MobProjectile::Render();
	}
}