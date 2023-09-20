#include "Bullet_FireOrb.h"
#include "SCRIPT_MobProjectile.h"

namespace sg
{
	Bullet_FireOrb::Bullet_FireOrb(Gobj_Monster* BulletOwner)
	{
		SetName(L"FireOrb");
		this->SetProjOwner(BulletOwner);
		mProjOwner = BulletOwner;
		mFirstPos = mProjOwner->GetComp<Transform>()->GetPosition();
		mType = eMProjType::Basic_RandDir;
		Bullet_FireOrb::Initialize();
	}
	Bullet_FireOrb::Bullet_FireOrb(Vector2 dir, Gobj_Monster* BulletOwner)
	{
		SetName(L"FireOrb");
		this->SetProjOwner(BulletOwner);
		mProjOwner = BulletOwner;
		mFirstPos = mProjOwner->GetComp<Transform>()->GetPosition();
		mType = eMProjType::Basic_Dir;
		mLastPos = Vector3(dir.x, dir.y, 0.0f);

		Bullet_FireOrb::Initialize();
	}
	Bullet_FireOrb::~Bullet_FireOrb()
	{
	}
	void Bullet_FireOrb::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		mAni = AddComp<Animator>();
		mCol = GetComp<Collider2D>();
		mCol->SetSize(Vector2(0.9f, 0.9f));
		SetMesh();
		SetMaterial(L"AnimationMaterial");
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"FireOrb", L"..\\Resources\\Monster\\Bosses\\fireorb.png");
		mAni->Create(L"Ani_FireOrb", atlas, Vector2::Zero, Vector2(8.0f, 8.0f), 4, Vector2::Zero, 0.05f);
		mMr->Initialize();
		mAni->PlayAnimation(L"Ani_FireOrb", true, true);

		AddComp<SCRIPT_MobProjectile>();
	}
	void Bullet_FireOrb::Update()
	{
		//SCRIPT_MobProjectile* script = GetComp<SCRIPT_MobProjectile>();
		//if (script == nullptr)
		//{
		//	script = AddComp<SCRIPT_MobProjectile>();
		//}
		Gobj_MobProjectile::Update();
	}
	void Bullet_FireOrb::LateUpdate()
	{
		Gobj_MobProjectile::LateUpdate();
	}
	void Bullet_FireOrb::Render()
	{
		Gobj_MobProjectile::Render();
	}
}