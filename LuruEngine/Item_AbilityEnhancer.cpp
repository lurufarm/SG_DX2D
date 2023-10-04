#include "Item_AbilityEnhancer.h"
#include <random>

namespace sg
{

	std::vector<int> Item_AbilityEnhancer::mItemIDs = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	std::vector<int> Item_AbilityEnhancer::mUsingItems = {};
	UINT Item_AbilityEnhancer::mItemSpawnCount[12] = {};

	Item_AbilityEnhancer::Item_AbilityEnhancer(int num)
	{
		mItemID = num;
		mActivate = false;
		Item_AbilityEnhancer::Initialize();
	}
	Item_AbilityEnhancer::~Item_AbilityEnhancer()
	{
	}
	void Item_AbilityEnhancer::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

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
		mMr->Initialize();

		switch (mItemID)
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
			switch (mItemID)
			{
			case 0: // 보너스 라이프 mLife
				DeleteinAbilityIDs(0);
				break;
			case 1: // 흡혈 ++ mHPStealRatio
				if (mItemSpawnCount[1] == 0)
				{
					DeleteinAbilityIDs(1);
					mUsingItems.push_back(1);
				}
				if (mItemSpawnCount[1] < 5)
					mItemSpawnCount[1]++;
				break;
			case 2: // 질긴 생명 ++ mHPHealRatio
				if (mItemSpawnCount[2] == 0)
				{
					DeleteinAbilityIDs(2);
					mUsingItems.push_back(2);
				}
				if (mItemSpawnCount[2] < 5)
					mItemSpawnCount[2]++;
				break;
			case 3: // 공격력 증가 mStrength
				if (mItemSpawnCount[3] == 0)
				{
					DeleteinAbilityIDs(3);
					mUsingItems.push_back(3);
				}
				if (mItemSpawnCount[3] < 5)
					mItemSpawnCount[3]++;
				break;
			case 4: // 방어력 증가 mDefence
				if (mItemSpawnCount[4] == 0)
				{
					DeleteinAbilityIDs(4);
					mUsingItems.push_back(4);
				}
				if (mItemSpawnCount[4] < 5)
					mItemSpawnCount[4]++;
				break;
			case 5: // 공격 범위 증가 mRange
				if (mItemSpawnCount[5] == 0)
				{
					DeleteinAbilityIDs(5);
					mUsingItems.push_back(5);
				}
				if (mItemSpawnCount[5] < 5)
					mItemSpawnCount[5]++;
				break;
			case 6: // 공격 지속 시간 증가 mAttackDuration
				if (mItemSpawnCount[6] == 0)
				{
					DeleteinAbilityIDs(6);
					mUsingItems.push_back(6);
				}
				if (mItemSpawnCount[6] < 5)
					mItemSpawnCount[6]++;
				break;
			case 7: // 공격 횟수 증가 (멀티샷) mAttackCount
				if (mItemSpawnCount[7] == 0)
				{
					DeleteinAbilityIDs(7);
					mUsingItems.push_back(7);
				}
				if (mItemSpawnCount[7] < 3)
					mItemSpawnCount[7]++;
				break;
			case 8: // 발사체 수 증가 mProjectiles
				if (mItemSpawnCount[8] == 0)
				{
					DeleteinAbilityIDs(8);
					mUsingItems.push_back(8);
				}
				if (mItemSpawnCount[8] < 5)
					mItemSpawnCount[8]++;
				break;
			case 9: // 공격 속도 증가 mAttackSpeed
				if (mItemSpawnCount[9] == 0)
				{
					DeleteinAbilityIDs(9);
					mUsingItems.push_back(9);
				}
				if (mItemSpawnCount[9] < 5)
					mItemSpawnCount[9]++;
				break;
			case 10: // 이동 속도 증가 mSpeed
				if (mItemSpawnCount[10] == 0)
				{
					DeleteinAbilityIDs(10);
					mUsingItems.push_back(10);
				}
				if (mItemSpawnCount[10] < 5)
					mItemSpawnCount[10]++;
				break;
			case 11: // 최대 체력 증가 mMaxHP
				if (mItemSpawnCount[11] == 0)
				{
					DeleteinAbilityIDs(11);
					mUsingItems.push_back(11);
				}
				if (mItemSpawnCount[11] < 5)
					mItemSpawnCount[11]++;
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
	void Item_AbilityEnhancer::DeleteinAbilityIDs(int a)
	{
		std::vector<int>::iterator iter = mItemIDs.begin();
		for (; iter != mItemIDs.end(); iter++)
		{
			if (a == *iter)
			{
				mItemIDs.erase(iter);
				break;
			}
		}
	}
	void Item_AbilityEnhancer::DeleteinUsingAbilities(int a)
	{
		std::vector<int>::iterator iter = mUsingItems.begin();
		for (; iter != mUsingItems.end(); iter++)
		{
			if (a == *iter)
			{
				mUsingItems.erase(iter);
				break;
			}
		}
	}
	int Item_AbilityEnhancer::RandomNumber()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		int a = 0;
		int b = 0;

		if (mItemIDs.size() > 7)
		{
			a = mItemIDs[0];
			b = mItemIDs[mItemIDs.size() - 1];
		}
		else
		{
			a = mUsingItems[0];
			b = mUsingItems[mUsingItems.size() - 1];
		}
		std::uniform_int_distribution<> dis(a, b);

		return dis(gen);
	}
}