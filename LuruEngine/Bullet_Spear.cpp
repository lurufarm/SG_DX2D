#include "Bullet_Spear.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "SCRIPT_MobProjectile.h"
#include "Effect_DustExplosion.h"

namespace sg
{
	Bullet_Spear::Bullet_Spear(Gobj_Monster* BulletOwner)
	{
		SetName(L"Spear");
		this->SetProjOwner(BulletOwner);
		mProjOwner = BulletOwner;

		Bullet_Spear::Initialize();
	}
	Bullet_Spear::~Bullet_Spear()
	{
		object::Instantiate<Effect_DustExplosion>(mTr->GetPosition(), eLayerType::Effect, mProjOwner->GetMyScene());
	}                                                                                                                                                             
	void Bullet_Spear::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		mType = eMProjType::Spear;
		SetMesh();
		SetMaterial(L"ImgSpear");
		mMr->Initialize();
		mCol = GetComp<Collider2D>();
		AddComp<SCRIPT_MobProjectile>();

	}
	void Bullet_Spear::Update()
	{
		Gobj_MobProjectile::Update();
	}
	void Bullet_Spear::LateUpdate()
	{
		Gobj_MobProjectile::LateUpdate();
	}
	void Bullet_Spear::Render()
	{
		Gobj_MobProjectile::Render();
	}
}