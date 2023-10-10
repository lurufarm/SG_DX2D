#include "Melee_Zombie.h"
#include "SCRIPT_MeleeZombie.h"

namespace sg
{
	Melee_Zombie::Melee_Zombie()
	{
		SetName(L"Zombie");

		mStat.mCurHP = 27;
		mStat.mMaxHP = 27;
		mStat.mStrength = 3;
		mStat.mDefence = 0.0f;
		mStat.mSpeed = 10.0f;
		mStat.mRange = 20.0f;
		mStat.mCooldown = 1.0f;
		mStat.dropEXP = 20.0f;

		Melee_Zombie::Initialize();
	}
	Melee_Zombie::~Melee_Zombie()
	{
	}
	void Melee_Zombie::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();
		mCol->SetSize(Vector2(0.5, 0.6f));
		mCol->SetCenter(Vector2(0.0f, -5.0f));
		mMSpeed = 0.15f;

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobZombie");

		mAni->Create(L"Ani_Zombie_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(28.0f, 24.0f), 5, Vector2::Zero, 0.15f);
		mAni->Create(L"Ani_Zombie_Move", mAtlas->GetTexture(), Vector2(0.0f, 24.0f), Vector2(28.0f, 24.0f), 8, Vector2::Zero, mMSpeed);
		mAni->Create(L"Ani_Zombie_Attack", mAtlas->GetTexture(), Vector2(0.0f, 48.0f), Vector2(28.0f, 24.0f), 7, Vector2::Zero, 0.15f);
		mAni->Create(L"Ani_Zombie_Death", mAtlas->GetTexture(), Vector2(0.0f, 72.0f), Vector2(28.0f, 24.0f), 10, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Zombie_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 96.0f), Vector2(28.0f, 24.0f), 7, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Zombie_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 120.0f), Vector2(28.0f, 24.0f), 10, Vector2::Zero, 0.05f);

		mMr->Initialize();
		AddComp<SCRIPT_MeleeZombie>();
		Monster_Melee::Initialize();
	}
	void Melee_Zombie::Update()
	{
		mAni->Create(L"Ani_Zombie_Move", mAtlas->GetTexture(), Vector2(0.0f, 24.0f), Vector2(28.0f, 24.0f), 8, Vector2::Zero, mMSpeed);
		Monster_Melee::Update();
	}
	void Melee_Zombie::LateUpdate()
	{
		Monster_Melee::LateUpdate();
	}
	void Melee_Zombie::Render()
	{
		Monster_Melee::Render();
	}
}