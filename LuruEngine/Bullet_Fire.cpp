#include "Bullet_Fire.h"
#include "..\Engine_SOURCE\sgParticleSystem.h"

#include "SCRIPT_MobProjectile.h"
#include "Gobj_Player.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	Bullet_Fire::Bullet_Fire(Gobj_Monster* BulletOwner)
	{
		SetName(L"BMummyBomb");
		this->SetProjOwner(BulletOwner);
		mProjOwner = BulletOwner;
		mFirstPos = mProjOwner->GetComp<Transform>()->GetPosition();
		mFirstPos.y -= 3.0f;

		Vector3 targetPos = Player->GetComp<Transform>()->GetPosition();
		if (mFirstPos.x > targetPos.x)
		{
			mFirstPos.x -= 5.0f;
		}
		else
		{
			mFirstPos.x += 5.0f;
		}

		Bullet_Fire::Initialize();
	}
	Bullet_Fire::~Bullet_Fire()
	{
	}
	void Bullet_Fire::Initialize()
	{
		mTr = GetComp<Transform>();
		mTr->SetPosition(mFirstPos);
		mType = eMProjType::Fire;
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		SetMaterial(L"TransparentMaterial");
		mMr->Initialize();

		mPs = new ParticleSystem();
		Vector4 scolor = Vector4(1.0f, 0.1f, 0.0f, 1.0f);
		Vector4 mcolor = Vector4(1.0f, 0.5f, 0.0f, 1.0f);
		Vector4 ecolor = Vector4(1.0f, 0.9f, 0.0f, 1.0f);
		mPs->SetParticleMaterial(L"ParticleMaterial2");
		mPs->SetTarget(Player);
		mPs->SetParticleOptions(300, Vector2(20.0, 20.0f), Vector2(3.0f, 25.0f), 50.0f, scolor, ecolor, mcolor, 0.5f, 0.1f);
		mPs = AddComp2<ParticleSystem>(mPs);

		Vector3 targetPos = Player->GetComp<Transform>()->GetPosition();
		Vector3 dir = targetPos - mFirstPos;
		dir.z = 0.0f;
		dir.Normalize();
		float angle = sgGetAngle(Vector2(dir.x, dir.y));
		float angle2 = angle;
		angle = sgGetAngleInRadian(angle + 90.0f);
		angle2 = sgGetAngleInRadian(angle2);
		mCol = GetComp<Collider2D>();
		mCol->SetSize(Vector2(15.0f, 75.0f));
		Vector2 pos2d = sgGetBeamPos(mCol->GetCSize().y / 2, angle2, Vector2(mFirstPos.x, mFirstPos.y));
		pos2d.x -= mFirstPos.x;
		pos2d.y -= mFirstPos.y;
		mCol->SetCenter(pos2d);
		mTr->SetRotation(0.0f, 0.0f, angle);

		AddComp<SCRIPT_MobProjectile>();

		mTime = 0.0f;
	}
	void Bullet_Fire::Update()
	{
		mTime += Time::DeltaTime();

		if (mTime >= 1.5f)
			SetState(GameObject::eState::Dead);
		
		Gobj_MobProjectile::Update();
	}
	void Bullet_Fire::LateUpdate()
	{
		Gobj_MobProjectile::LateUpdate();
	}
	void Bullet_Fire::Render()
	{
		Gobj_MobProjectile::Render();
	}
}