#include "Boss_SkelKnight.h"
#include "Gobj_Monster.h"
#include "Monster_Ranged.h"
#include "SCRIPT_SkelKnight.h"

namespace sg
{
	Boss_SkelKnight::Boss_SkelKnight()
	{
		SetName(L"SkelKnight");

		mStat.mCurHP = 100;
		mStat.mMaxHP = 100;
		mStat.mStrength = 7;
		mStat.mDefence = 0.3f;
		mStat.mSpeed = 10.0f;
		mStat.mRange = 180.0f;
		mStat.mCooldown = 2.3f;
		mStat.dropEXP = 20.0f;

		Boss_SkelKnight::Initialize();
	}
	Boss_SkelKnight::~Boss_SkelKnight()
	{
	}
	void Boss_SkelKnight::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobSkelKnight");

		mAni->Create(L"Ani_SkelKnight_Spawn", mAtlas->GetTexture(), Vector2::Zero, Vector2(56.0f, 72.0f), 22, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_SkelKnight_Idle", mAtlas->GetTexture(), Vector2(0.0f, 72.0f), Vector2(56.0f, 72.0f), 6, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_SkelKnight_Move", mAtlas->GetTexture(), Vector2(0.0f, 144.0f), Vector2(56.0f, 72.0f), 8, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_SkelKnight_Attack", mAtlas->GetTexture(), Vector2(0.0f, 216.0f), Vector2(56.0f, 72.0f), 13, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_SkelKnight_Attack2", mAtlas->GetTexture(), Vector2(0.0f, 288.0f), Vector2(56.0f, 72.0f), 11, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_SkelKnight_Attack3", mAtlas->GetTexture(), Vector2(0.0f, 360.0f), Vector2(56.0f, 72.0f), 16, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_SkelKnight_Attack4", mAtlas->GetTexture(), Vector2(0.0f, 432.0f), Vector2(56.0f, 72.0f), 20, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_SkelKnight_Death", mAtlas->GetTexture(), Vector2(0.0f, 504.0f), Vector2(56.0f, 72.0f), 26, Vector2::Zero, 0.08f);

		mMr->Initialize();
		mCol->SetCenter(Vector2(0.0f, -15.0f));
		mCol->SetSize(Vector2(0.5f, 0.6f));
		AddComp<SCRIPT_SkelKnight>();
		Gobj_Monster::Initialize();
	}
	void Boss_SkelKnight::Update()
	{
		Gobj_Monster::Update();
	}
	void Boss_SkelKnight::LateUpdate()
	{
		Gobj_Monster::LateUpdate();
	}
	void Boss_SkelKnight::Render()
	{
		Gobj_Monster::Render();
	}
}