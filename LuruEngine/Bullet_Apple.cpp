#include "Bullet_Apple.h"

#include "..\Engine_SOURCE\sgObject.h"
#include "Boss_OldEnt.h"

#include "SCRIPT_MobProjectile.h"
#include "Bullet_SlicedApple.h"



namespace sg
{
	Bullet_Apple::Bullet_Apple(Gobj_Monster* BulletOwner)
	{
		SetName(L"EntApple");
		this->SetProjOwner(BulletOwner);
		mProjOwner = BulletOwner;
		mFirstPos = mProjOwner->GetComp<Transform>()->GetPosition();
		Bullet_Apple::Initialize();
	}
	Bullet_Apple::~Bullet_Apple()
	{
		//((Boss_OldEnt*)mProjOwner)->SetProjPos(this->GetComp<Transform>()->GetPosition());
	}
	void Bullet_Apple::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		mAni = AddComp<Animator>();
		mCol = GetComp<Collider2D>();
		mType = eMProjType::EntRock;
		SetMesh();
		SetMaterial(L"AnimationMaterial");

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"EntApple", L"..\\Resources\\Monster\\Bosses\\apple.png");
		mAni->Create(L"Ani_EntApple", atlas, Vector2::Zero, Vector2(14.0f, 14.0f), 4, Vector2::Zero, 0.05f);
		mMr->Initialize();
		mAni->PlayAnimation(L"Ani_EntApple", true, true);

		AddComp<SCRIPT_MobProjectile>();
	}
	void Bullet_Apple::Update()
	{
		((Boss_OldEnt*)mProjOwner)->SetProjPos(this->GetComp<Transform>()->GetPosition());
		Gobj_MobProjectile::Update();
	}
	void Bullet_Apple::LateUpdate()
	{
		Gobj_MobProjectile::LateUpdate();
	}
	void Bullet_Apple::Render()
	{
		Gobj_MobProjectile::Render();
	}
}