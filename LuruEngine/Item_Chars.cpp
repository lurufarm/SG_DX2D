#include "Item_Chars.h"
#include <random>

namespace sg
{
	std::vector<int> Item_Chars::mCharIDs = { 20, 21, 22 };
	std::vector<int> Item_Chars::mUsingCharIDs = {};
	UINT Item_Chars::mItemSpawnCount[10] = {};

	Item_Chars::Item_Chars(int num)
	{
		mItemID = num;
		mActivate = false;
		Item_Chars::Initialize();
	}
	Item_Chars::~Item_Chars()
	{
	}
	void Item_Chars::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"Item_Characters", L"..\\Resources\\Item\\Characters.png");

		mAni->Create(L"Ani_Item_Cheese", atlas, Vector2::Zero, Vector2(20.0f, 24.0f), 9, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Item_Lucy", atlas, Vector2(0.0f, 24.0f), Vector2(20.0f, 24.0f), 9, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Item_Robo", atlas, Vector2(0.0f, 48.0f), Vector2(20.0f, 24.0f), 9, Vector2::Zero, 0.05f);
		mMr->Initialize();

		switch (mItemID)
		{
		case 20: // 치즈
			mAni->PlayAnimation(L"Ani_Item_Cheese", false, true);
			break;
		case 21: // 루시
			mAni->PlayAnimation(L"Ani_Item_Lucy", false, true);
			break;
		case 22: // 로보
			mAni->PlayAnimation(L"Ani_Item_Robo", false, true);
			break;
		}
	}
	void Item_Chars::Update()
	{
		for (size_t i = 20; i < 23; i++)
		{
			if (mItemSpawnCount[i - 20] >= 5)
				DeleteinUsingChars(i);
		}

		if (mActivate)
		{
			switch (mItemID)
			{
			case 20: // 치즈
				if (mItemSpawnCount[0] == 0)
				{
					DeleteinCharIDs(20);
					mUsingCharIDs.push_back(20);
				}
				if (mItemSpawnCount[0] < 5)
					mItemSpawnCount[0]++;
				break;
			case 21: // 루시
				if (mItemSpawnCount[1] == 0)
				{
					DeleteinCharIDs(21);
					mUsingCharIDs.push_back(21);
				}
				if (mItemSpawnCount[1] < 5)
					mItemSpawnCount[1]++;
				break;
			case 22: // 로보
				if (mItemSpawnCount[2] == 0)
				{
					DeleteinCharIDs(22);
					mUsingCharIDs.push_back(22);
				}
				if (mItemSpawnCount[2] < 5)
					mItemSpawnCount[2]++;
				break;
			}
		}
		Gobj_Item::Update();
	}
	void Item_Chars::LateUpdate()
	{
		Gobj_Item::LateUpdate();
	}
	void Item_Chars::Render()
	{
		Gobj_Item::Render();
	}
	void Item_Chars::DeleteinCharIDs(int a)
	{
		std::vector<int>::iterator iter = mCharIDs.begin();
		for (; iter != mCharIDs.end(); iter++)
		{
			if (a == *iter)
			{
				mCharIDs.erase(iter);
				break;
			}
		}
	}
	void Item_Chars::DeleteinUsingChars(int a)
	{
		std::vector<int>::iterator iter = mUsingCharIDs.begin();
		for (; iter != mUsingCharIDs.end(); iter++)
		{
			if (a == *iter)
			{
				mUsingCharIDs.erase(iter);
				break;
			}
		}
	}
	int Item_Chars::RandomNumber()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		int a = 0;
		int b = 0;

		if (mUsingCharIDs.size() < 4)
		{
			a = mCharIDs[0];
			b = mCharIDs[mCharIDs.size() - 1];
		}
		else
		{
			a = mUsingCharIDs[0];
			b = mUsingCharIDs[mUsingCharIDs.size() - 1];
		}
		std::uniform_int_distribution<> dis(a, b);

		return dis(gen);
	}
}