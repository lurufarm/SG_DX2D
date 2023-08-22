#include "Bullet_SlicedApple.h"

#include "Boss_OldEnt.h"
#include "SCRIPT_MobProjectile.h"
#include "SCRIPT_Boss.h"


namespace sg
{
	Bullet_SlicedApple::Bullet_SlicedApple(Vector3 fPos, int dir)
	{
		SetName(L"EntSlicedApple");
		this->SetProjOwner(nullptr);
		mFirstPos = fPos;
		mTr = GetComp<Transform>();
		mTr->SetPosition(fPos);
		if (dir == 0) // 위
			mLastPos = fPos + Vector3(0, 10, 0);
		else if (dir == 1) // 오른쪽
			mLastPos = fPos + Vector3(10, 0, 0);
		else if (dir == 2) // 아래
			mLastPos = fPos + Vector3(0, -10, 0);
		else if (dir == 3) // 왼쪽
			mLastPos = fPos + Vector3(-10, 0, 0);

		Bullet_SlicedApple::Initialize();
	}
	Bullet_SlicedApple::~Bullet_SlicedApple()
	{
	}
	void Bullet_SlicedApple::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		mAni = AddComp<Animator>();
		mCol = GetComp<Collider2D>();
		mType = eMProjType::Basic;
		SetMesh();
		SetMaterial(L"AnimationMaterial");

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"EntSlicedApple", L"..\\Resources\\Monster\\Bosses\\slicedapple.png");
		mAni->Create(L"Ani_EntSlicedApple", atlas, Vector2::Zero, Vector2(13.0f, 13.0f), 4, Vector2::Zero, 0.1f);
		mAni->PlayAnimation(L"Ani_EntSlicedApple", true, true);
		mMr->Initialize();

		mCol->SetSize(Vector2(0.5f, 0.5f));

		AddComp<SCRIPT_MobProjectile>();
	}
	void Bullet_SlicedApple::Update()
	{
		Gobj_MobProjectile::Update();
	}
	void Bullet_SlicedApple::LateUpdate()
	{
		Gobj_MobProjectile::LateUpdate();
	}
	void Bullet_SlicedApple::Render()
	{
		Gobj_MobProjectile::Render();
	}
}