#include "Bullet_SKGroundFire.h"
#include "SCRIPT_MobProjectile.h"

namespace sg
{
	Bullet_SKGroundFire::Bullet_SKGroundFire(Vector2 dir, Gobj_Monster* BulletOwner)
	{
		SetName(L"SKGroundFire");
		mDir = dir;
		mProjOwner = BulletOwner;
		Bullet_SKGroundFire::Initialize();
	}
	Bullet_SKGroundFire::~Bullet_SKGroundFire()
	{
	}
	void Bullet_SKGroundFire::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		mAni = AddComp<Animator>();
		mCol = GetComp<Collider2D>();
		mType = eMProjType::Basic_NearCardinalDir;

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"Bullet_GroundFire", L"..\\Resources\\Monster\\Bosses\\sk_groundfire.png");
		mAni->Create(L"Ani_Bullet_GroundFire", atlas, Vector2::Zero, Vector2(10.0f, 52.0f), 7, Vector2::Zero, 0.2f);
		mAni->PlayAnimation(L"Ani_Bullet_GroundFire", false, true);

		mMr->Initialize();

		mLastPos = Vector3(mDir.x, mDir.y, 0.0f);

		AddComp<SCRIPT_MobProjectile>();


	}
	void Bullet_SKGroundFire::Update()
	{
		if (mAni->GetActiveAni()->IsComplete())
			SetState(eState::Dead);

		Vector3 pos = mTr->GetPosition();
		pos.z = -0.1f;
		mTr->SetPosition(pos);

		Gobj_MobProjectile::Update();
	}
	void Bullet_SKGroundFire::LateUpdate()
	{
		Gobj_MobProjectile::LateUpdate();
	}
	void Bullet_SKGroundFire::Render()
	{
		Gobj_MobProjectile::Render();
	}
}