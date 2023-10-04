#pragma once
#include "Gobj_Item.h"

namespace sg
{
	class Item_AbilityEnhancer : public Gobj_Item
	{
	public:
		Item_AbilityEnhancer(int num);
		~Item_AbilityEnhancer();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void DeleteinAbilityIDs(int a);
		void DeleteinUsingAbilities(int a);

		int RandomNumber();

		void SetItemActivate(bool value) { mActivate = value; }
		
	private:

		static UINT mItemSpawnCount[12];
		static std::vector<int>mItemIDs;
		static std::vector<int>mUsingItems;
	};
}
