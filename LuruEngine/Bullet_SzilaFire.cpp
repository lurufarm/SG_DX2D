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

		Gobj_Bullet::Initialize();
		mFirstPos.y -= 3.0f;
		mTr->SetPosition(mFirstPos);

		mPs = new ParticleSystem(); // 재
		Vector4 scolor = Vector4(0.5f, 0.0f, 0.0f, 0.8f);
		Vector4 mcolor = Vector4(0.0f, 0.0f, 0.0f, 0.8f);
		Vector4 ecolor = Vector4(0.0f, 0.0f, 0.5f, 0.3f);
		mPs->SetParticleMaterial(L"ParticleMaterial2");
		mPs->SetTarget(this->mTarget);
		mPs->SetParticleOptions(100, Vector2(30.0, 30.0f), Vector2(7.0f, 10.0f), 30.0f, scolor, ecolor, mcolor, 0.8f, 0.1f);
		mPs = AddComp2<ParticleSystem>(mPs);

		ParticleSystem* mPs2 = new ParticleSystem(); // 초록 불
		Vector4 scolor2 = Vector4(0.0f, 1.0f, 0.0f, 0.5f);
		Vector4 mcolor2 = Vector4(0.0f, 1.0f, 0.0f, 0.8f);
		Vector4 ecolor2 = Vector4(1.0f, 0.0f, 0.0f, 0.8f);
		mPs2->SetParticleMaterial(L"ParticleMaterial2");
		mPs2->SetTarget(this->mTarget);
		mPs2->SetParticleOptions(200 * mThisNum, Vector2(20.0, 5.0f * mThisNum), Vector2(25.0f, 35.0f), 40.0f, scolor2, mcolor2, ecolor2, 0.5f, 0.05f);
		mPs2 = AddComp2<ParticleSystem>(mPs2);

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