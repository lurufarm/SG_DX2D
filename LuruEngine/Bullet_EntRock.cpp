#include "Bullet_EntRock.h"
#include "SCRIPT_MobProjectile.h"

namespace sg
{
	Bullet_EntRock::Bullet_EntRock(Gobj_Monster* BulletOwner)
	{
		SetName(L"PoisonOrb");
		this->SetProjOwner(BulletOwner);
		mProjOwner = BulletOwner;
		mFirstPos = mProjOwner->GetComp<Transform>()->GetPosition();
		Bullet_EntRock::Initialize();
	}
	Bullet_EntRock::~Bullet_EntRock()
	{
	}
	void Bullet_EntRock::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		mAni = AddComp<Animator>();
		mCol = GetComp<Collider2D>();
		mType = eMProjType::EntRock;
		SetMesh();
		SetMaterial(L"AnimationMaterial");

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"EntRock", L"..\\Resources\\Monster\\EntRock.png");
		mAni->Create(L"Ani_EntRock", atlas, Vector2::Zero, Vector2(13.0f, 13.0f), 4, Vector2::Zero, 0.05f);
		mMr->Initialize();
		mAni->PlayAnimation(L"Ani_EntRock", true, true);

		AddComp<SCRIPT_MobProjectile>();
	}
	void Bullet_EntRock::Update()
	{
		Gobj_MobProjectile::Update();
	}
	void Bullet_EntRock::LateUpdate()
	{
		Gobj_MobProjectile::LateUpdate();
	}
	void Bullet_EntRock::Render()
	{
		Gobj_MobProjectile::Render();
	}
}