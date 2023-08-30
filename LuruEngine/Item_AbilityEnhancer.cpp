#include "Item_AbilityEnhancer.h"
#include <random>

namespace sg
{

	std::vector<int> Item_AbilityEnhancer::mAbilityIDs = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	std::vector<int> Item_AbilityEnhancer::mUsingAbilities = {};
	UINT Item_AbilityEnhancer::mItemSpawnCount[12] = {};

	Item_AbilityEnhancer::Item_AbilityEnhancer()
	{
		mAbilityID = RandomNumber();
	}
	Item_AbilityEnhancer::~Item_AbilityEnhancer()
	{
	}
	void Item_AbilityEnhancer::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"Item_Enhencers", L"..\\Resources\\Item\\Enhencers.png");

		mAni->Create(L"Ani_BonusLife", atlas, Vector2::Zero, Vector2(20.0f, 24.0f), 9, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_StealHP", atlas, Vector2(0.0f, 24.0f), Vector2(20.0f, 24.0f), 9, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Heal", atlas, Vector2(0.0f, 48.0f), Vector2(20.0f, 24.0f), 9, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_EnhenceStrength", atlas, Vector2(0.0f, 72.0f), Vector2(20.0f, 24.0f), 9, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_EnhenceDefence", atlas, Vector2(0.0f, 96.0f), Vector2(20.0f, 24.0f), 9, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_EnhenceRange", atlas, Vector2(0.0f, 120.0f), Vector2(20.0f, 24.0f), 9, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_EnhenceADuration", atlas, Vector2(0.0f, 144.0f), Vector2(20.0f, 24.0f), 9, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_EnhenceACount", atlas, Vector2(0.0f, 168.0f), Vector2(20.0f, 24.0f), 9, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_EnhenceProjNum", atlas, Vector2(0.0f, 192.0f), Vector2(20.0f, 24.0f), 9, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_EnhenceASpeed", atlas, Vector2(0.0f, 216.0f), Vector2(20.0f, 24.0f), 9, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_EnhenceMSpeed", atlas, Vector2(0.0f, 240.0f), Vector2(20.0f, 24.0f), 9, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_EnhenceMaxHP", atlas, Vector2(0.0f, 264.0f), Vector2(20.0f, 24.0f), 9, Vector2::Zero, 0.05f);



		switch (mAbilityID)
		{
		case 0: // 보너스 라이프 mLife
			mAni->PlayAnimation(L"Ani_BonusLife", false, true);
			break;
		case 1: // 흡혈 ++ mHPStealRatio
			mAni->PlayAnimation(L"Ani_StealHP", false, true);
			break;
		case 2: // 질긴 생명 ++ mHPHealRatio
			mAni->PlayAnimation(L"Ani_Heal", false, true);
			break;
		case 3: // 공격력 증가 mStrength
			mAni->PlayAnimation(L"Ani_EnhenceStrength", false, true);
			break;
		case 4: // 방어력 증가 mDefence
			mAni->PlayAnimation(L"Ani_EnhenceDefence", false, true);
			break;
		case 5: // 공격 범위 증가 mRange
			mAni->PlayAnimation(L"Ani_EnhenceRange", false, true);
			break;
		case 6: // 공격 지속 시간 증가 mAttackDuration
			mAni->PlayAnimation(L"Ani_EnhenceADuration", false, true);
			break;
		case 7: // 공격 횟수 증가 (멀티샷) mAttackCount
			mAni->PlayAnimation(L"Ani_EnhenceACount", false, true);
			break;
		case 8: // 발사체 수 증가 mProjectiles
			mAni->PlayAnimation(L"Ani_EnhenceProjNum", false, true);
			break;
		case 9: // 공격 속도 증가 mAttackSpeed
			mAni->PlayAnimation(L"Ani_EnhenceASpeed", false, true);
			break;
		case 10: // 이동 속도 증가 mSpeed
			mAni->PlayAnimation(L"Ani_EnhenceMSpeed", false, true);
			break;
		case 11: // 최대 체력 증가 mMaxHP
			mAni->PlayAnimation(L"Ani_EnhenceMaxHP", false, true);
			break;
		}
		
		mMr->Initialize();

	}
	void Item_AbilityEnhancer::Update()
	{
		if (mActivate)
		{
			switch (mAbilityID)
			{
			case 0: // 보너스 라이프 mLife
				mPlayer->BonusLife();
				mAbilityIDs.erase(mAbilityIDs.begin());
				break;
			case 1: // 흡혈 ++ mHPStealRatio
				mAni->PlayAnimation(L"Ani_StealHP", false, true);
				mAbilityIDs.erase()
				if (mItemSpawnCount[1] < 3)
					mItemSpawnCount[1]++;
				else if (mItemSpawnCount[1] >= 3)
					mUsingAbilities.erase()
				break;
			case 2: // 질긴 생명 ++ mHPHealRatio
				mAni->PlayAnimation(L"Ani_Heal", false, true);
				break;
			case 3: // 공격력 증가 mStrength
				mAni->PlayAnimation(L"Ani_EnhenceStrength", false, true);
				break;
			case 4: // 방어력 증가 mDefence
				mAni->PlayAnimation(L"Ani_EnhenceDefence", false, true);
				break;
			case 5: // 공격 범위 증가 mRange
				mAni->PlayAnimation(L"Ani_EnhenceRange", false, true);
				break;
			case 6: // 공격 지속 시간 증가 mAttackDuration
				mAni->PlayAnimation(L"Ani_EnhenceADuration", false, true);
				break;
			case 7: // 공격 횟수 증가 (멀티샷) mAttackCount
				mAni->PlayAnimation(L"Ani_EnhenceACount", false, true);
				break;
			case 8: // 발사체 수 증가 mProjectiles
				mAni->PlayAnimation(L"Ani_EnhenceProjNum", false, true);
				break;
			case 9: // 공격 속도 증가 mAttackSpeed
				mAni->PlayAnimation(L"Ani_EnhenceASpeed", false, true);
				break;
			case 10: // 이동 속도 증가 mSpeed
				mAni->PlayAnimation(L"Ani_EnhenceMSpeed", false, true);
				break;
			case 11: // 최대 체력 증가 mMaxHP
				mAni->PlayAnimation(L"Ani_EnhenceMaxHP", false, true);
				break;
			}
		}

		Gobj_Item::Update();
	}
	void Item_AbilityEnhancer::LateUpdate()
	{
		Gobj_Item::LateUpdate();
	}
	void Item_AbilityEnhancer::Render()
	{
		Gobj_Item::Render();
	}
	UINT Item_AbilityEnhancer::RandomNumber()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		int a = 0;
		int b = 0;

		if (mAbilityIDs.size() > 7)
		{
			a = mAbilityIDs[0];
			b = mAbilityIDs[mAbilityIDs.size() - 1];
		}
		else
		{
			a = mUsingAbilities[0];
			b = mUsingAbilities[mUsingAbilities.size() - 1];
		}
		std::uniform_int_distribution<> dis(a, b);

		return dis(gen);
	}
}