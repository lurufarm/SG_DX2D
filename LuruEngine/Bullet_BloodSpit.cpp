#include "Bullet_BloodSpit.h"
#include "SCRIPT_MobProjectile.h"
#include "..\Engine_SOURCE\sgParticleSystem.h"
#include "Gobj_Player.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	Bullet_BloodSpit::Bullet_BloodSpit(Gobj_Monster* BulletOwner, Vector3 dir)
	{
		SetName(L"BloodSpit");
		this->SetProjOwner(BulletOwner);
		mProjOwner = BulletOwner;
		mFirstPos = mProjOwner->GetComp<Transform>()->GetPosition();
		mLastPos = dir;
		Bullet_BloodSpit::Initialize();
	}
	Bullet_BloodSpit::~Bullet_BloodSpit()
	{
	}
	void Bullet_BloodSpit::Initialize()
	{
		mTr = GetComp<Transform>();
		mTr->SetPosition(mFirstPos);
		mTr->SetScale(0.2f, 2.0f, 1.0f);
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mType = eMProjType::BloodSpit;

		SetMesh();
		SetMaterial(L"ImgEyeBallProj");

		mMr->Initialize();


		ParticleSystem* mPs = new ParticleSystem();
		Vector4 scolor = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		Vector4 mcolor = Vector4(1.0f, 0.7f, 0.0f, 0.6f);
		Vector4 ecolor = Vector4(1.0f, 0.0f, 0.0f, 0.2f);
		mPs->SetParticleMaterial(L"ParticleMaterial2");
		mPs->SetTarget(this);
		mPs->SetParticleOptions(100, Vector2(10.0, 100.0f), Vector2(3.0f, 4.0f), 3.0f, scolor, ecolor, mcolor, 2.0f, 0.01f);
		mPs = this->AddComp2<ParticleSystem>(mPs);


		AddComp<SCRIPT_MobProjectile>();
	}
	void Bullet_BloodSpit::Update()
	{
		Gobj_MobProjectile::Update();
	}
	void Bullet_BloodSpit::LateUpdate()
	{
		Gobj_MobProjectile::LateUpdate();
	}
	void Bullet_BloodSpit::Render()
	{
		Gobj_MobProjectile::Render();
	}
}