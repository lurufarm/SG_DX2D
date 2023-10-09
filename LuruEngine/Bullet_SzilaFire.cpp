#include "Bullet_SzilaFire.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "..\Engine_SOURCE\sgParticleSystem.h"
#include "Gobj_Player.h"
#include "SCRIPT_Bullet.h"
#include "SCRIPT_Player.h"
#include "Gobj_Character.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	Bullet_SzilaFire::Bullet_SzilaFire()
	{
		SetName(L"SzilaFire");
		mThisNum = 1;
		Bullet_SzilaFire::Initialize();
	}
	Bullet_SzilaFire::Bullet_SzilaFire(int num)
	{
		SetName(L"SzilaFire");
		mThisNum = num;
		Bullet_SzilaFire::Initialize();
	}
	Bullet_SzilaFire::~Bullet_SzilaFire()
	{
	}
	void Bullet_SzilaFire::Initialize()
	{
		mBulletOwner = SceneManager::GetChar(L"Szila");

		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mType = eBulletType::Szila;
		SetMesh();
		SetMaterial(L"TransparentMaterial");
		mMr->Initialize();
		
		//mFirstPos = mBulletOwner->GetComp<Transform>()->GetPosition();

		Gobj_Bullet::Initialize();
		mFirstPos.y -= 3.0f;
		mTr->SetPosition(mFirstPos);

		mPs = new ParticleSystem();
		Vector4 scolor = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		Vector4 mcolor = Vector4(0.8f, 1.0f, 0.0f, 1.0f);
		Vector4 ecolor = Vector4(1.0f, 0.9f, 0.0f, 1.0f);
		mPs->SetParticleMaterial(L"ParticleMaterial2");
		mPs->SetTarget(this->mTarget);
		mPs->SetParticleOptions(300, Vector2(20.0, 5.0f), Vector2(10.0f, 30.0f), 60.0f, scolor, ecolor, mcolor, 0.5f, 0.1f);
		mPs = AddComp2<ParticleSystem>(mPs);

		ParticleSystem* mPs2 = new ParticleSystem();
		Vector4 scolor2 = Vector4(0.8f, 0.2f, 0.0f, 1.0f);
		Vector4 mcolor2 = Vector4(1.0f, 0.5f, 0.1f, 1.0f);
		Vector4 ecolor2 = Vector4(0.2f, 1.0f, 0.0f, 1.0f);
		mPs2->SetParticleMaterial(L"ParticleMaterial2");
		mPs2->SetTarget(this->mTarget);
		mPs2->SetParticleOptions(300, Vector2(20.0, 5.0f), Vector2(10.0f, 30.0f), 60.0f, scolor2, mcolor2, ecolor2, 0.5f, 0.1f);
		mPs2 = AddComp2<ParticleSystem>(mPs2);

		ParticleSystem* mPs3 = new ParticleSystem();
		mPs3->SetParticleMaterial(L"ParticleMaterial2");
		mPs3->SetTarget(this->mTarget);
		mPs3->SetParticleOptions(300, Vector2(20.0, 5.0f), Vector2(10.0f, 30.0f), 60.0f, scolor, ecolor, mcolor, 0.5f, 0.1f);
		mPs3 = AddComp2<ParticleSystem>(mPs3);


		AddComp<SCRIPT_Bullet>();

	}
	void Bullet_SzilaFire::Update()
	{
		Gobj_Bullet::Update();
	}
	void Bullet_SzilaFire::LateUpdate()
	{
		Gobj_Bullet::LateUpdate();
	}
	void Bullet_SzilaFire::Render()
	{
		Gobj_Bullet::Render();
	}
}