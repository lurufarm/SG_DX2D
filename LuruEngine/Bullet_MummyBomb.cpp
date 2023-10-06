#include "Bullet_MummyBomb.h"
#include "SCRIPT_MobProjectile.h"

namespace sg
{
	Bullet_MummyBomb::Bullet_MummyBomb(Gobj_Monster* BulletOwner)
	{
		SetName(L"BMummyBomb");
		this->SetProjOwner(BulletOwner);
		mProjOwner = BulletOwner;
		mFirstPos = mProjOwner->GetComp<Transform>()->GetPosition();
		Bullet_MummyBomb::Initialize();
	}
	Bullet_MummyBomb::~Bullet_MummyBomb()
	{
	}
	void Bullet_MummyBomb::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		mAni = AddComp<Animator>();
		mCol = GetComp<Collider2D>();
		mType = eMProjType::MummyBomb;
		SetMesh();
		SetMaterial(L"AnimationMaterial");

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"MummyBomb", L"..\\Resources\\Character\\Lucy\\LucyBomb.png");
		mAni->Create(L"Ani_MummyBomb", atlas, Vector2::Zero, Vector2(15.0f, 15.0f), 4, Vector2::Zero, 0.1f);
		mMr->Initialize();
		mAni->PlayAnimation(L"Ani_MummyBomb", true, true);

		AddComp<SCRIPT_MobProjectile>();
	}
	void Bullet_MummyBomb::Update()
	{
		Gobj_MobProjectile::Update();
	}
	void Bullet_MummyBomb::LateUpdate()
	{
		Gobj_MobProjectile::LateUpdate();
	}
	void Bullet_MummyBomb::Render()
	{
		Gobj_MobProjectile::Render();
	}
}