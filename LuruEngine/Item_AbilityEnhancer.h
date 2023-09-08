#pragma once
#include "Gobj_Item.h"

namespace sg
{
	class Item_AbilityEnhancer : public Gobj_Item
	{
	public:
		Item_AbilityEnhancer();
		~Item_AbilityEnhancer();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void DeleteinAbilityIDs(int a);
		void DeleteinUsingAbilities(int a);

		//void SetItemID(int a) { mItemID = a; }
		//int GetItemID() { return mItemID; }

		int RandomNumber();
		

	private:

		//int mItemID;
		bool mActivate;
		static UINT mItemSpawnCount[12];
		static std::vector<int>mItemIDs;
		static std::vector<int>mUsingItems;
	};
}
