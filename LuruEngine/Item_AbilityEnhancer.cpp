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
		for (size_t i = 0; i < 12; i++)
		{
			if (mItemSpawnCount[i] >= 5)
				DeleteinUsingAbilities(i);
			if (mItemSpawnCount[7] >= 3)
				DeleteinUsingAbilities(7);
		}

		if (mActivate)
		{
			switch (mAbilityID)
			{
			case 0: // 보너스 라이프 mLife
				mPlayer->BonusLife();
				DeleteinAbilityIDs(0);
				break;
			case 1: // 흡혈 ++ mHPStealRatio
				mPlayer->EnhenceHPStealRatio();
				if (mItemSpawnCount[1] == 0)
				{
					DeleteinAbilityIDs(1);
					mUsingAbilities.push_back(1);
				}
				if (mItemSpawnCount[1] < 5)
					mItemSpawnCount[1]++;
				break;
			case 2: // 질긴 생명 ++ mHPHealRatio
				mPlayer->EnhenceHPHealRatio();
				if (mItemSpawnCount[2] == 0)
				{
					DeleteinAbilityIDs(2);
					mUsingAbilities.push_back(2);
				}
				if (mItemSpawnCount[2] < 5)
					mItemSpawnCount[2]++;
				break;
			case 3: // 공격력 증가 mStrength
				mPlayer->EnhenceStrength();
				if (mItemSpawnCount[3] == 0)
				{
					DeleteinAbilityIDs(3);
					mUsingAbilities.push_back(3);
				}
				if (mItemSpawnCount[3] < 5)
					mItemSpawnCount[3]++;
				break;
			case 4: // 방어력 증가 mDefence
				mPlayer->EnhenceDefence();
				if (mItemSpawnCount[4] == 0)
				{
					DeleteinAbilityIDs(4);
					mUsingAbilities.push_back(4);
				}
				if (mItemSpawnCount[4] < 5)
					mItemSpawnCount[4]++;
				break;
			case 5: // 공격 범위 증가 mRange
				mPlayer->EnhenceRange();
				if (mItemSpawnCount[5] == 0)
				{
					DeleteinAbilityIDs(5);
					mUsingAbilities.push_back(5);
				}
				if (mItemSpawnCount[5] < 5)
					mItemSpawnCount[5]++;
				break;
			case 6: // 공격 지속 시간 증가 mAttackDuration
				mPlayer->EnhenceAttackDuration();
				if (mItemSpawnCount[6] == 0)
				{
					DeleteinAbilityIDs(6);
					mUsingAbilities.push_back(6);
				}
				if (mItemSpawnCount[6] < 5)
					mItemSpawnCount[6]++;
				break;
			case 7: // 공격 횟수 증가 (멀티샷) mAttackCount
				mPlayer->EnhenceAttackCount();
				if (mItemSpawnCount[7] == 0)
				{
					DeleteinAbilityIDs(7);
					mUsingAbilities.push_back(7);
				}
				if (mItemSpawnCount[7] < 3)
					mItemSpawnCount[7]++;
				break;
			case 8: // 발사체 수 증가 mProjectiles
				mPlayer->EnhenceProjectileCount();
				if (mItemSpawnCount[8] == 0)
				{
					DeleteinAbilityIDs(8);
					mUsingAbilities.push_back(8);
				}
				if (mItemSpawnCount[8] < 5)
					mItemSpawnCount[8]++;
				break;
			case 9: // 공격 속도 증가 mAttackSpeed
				mPlayer->EnhenceAttackSpeed();
				if (mItemSpawnCount[9] == 0)
				{
					DeleteinAbilityIDs(9);
					mUsingAbilities.push_back(9);
				}
				if (mItemSpawnCount[9] < 5)
					mItemSpawnCount[9]++;
				break;
			case 10: // 이동 속도 증가 mSpeed
				mPlayer->EnhenceSpeed();
				if (mItemSpawnCount[10] == 0)
				{
					DeleteinAbilityIDs(10);
					mUsingAbilities.push_back(10);
				}
				if (mItemSpawnCount[10] < 5)
					mItemSpawnCount[10]++;
				break;
			case 11: // 최대 체력 증가 mMaxHP
				mPlayer->EnhenceMaxHP();
				if (mItemSpawnCount[11] == 0)
				{
					DeleteinAbilityIDs(11);
					mUsingAbilities.push_back(11);
				}
				if (mItemSpawnCount[11] < 5)
					mItemSpawnCount[11]++;
				break;
			}
			SetState(GameObject::eState::Dead);
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
	void Item_AbilityEnhancer::DeleteinAbilityIDs(int a)
	{
		std::vector<int>::iterator iter = mAbilityIDs.begin();
		for (; iter != mAbilityIDs.end(); iter++)
		{
			if (a == *iter)
			{
				mAbilityIDs.erase(iter);
			}
		}
	}
	void Item_AbilityEnhancer::DeleteinUsingAbilities(int a)
	{
		std::vector<int>::iterator iter = mUsingAbilities.begin();
		for (; iter != mUsingAbilities.end(); iter++)
		{
			if (a == *iter)
			{
				mUsingAbilities.erase(iter);
			}
		}
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