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

		void DeleteID(int a);

		UINT RandomNumber();

	private:

		UINT mAbilityID;
		bool mActivate;
		static UINT mItemSpawnCount[12];
		static std::vector<int>mAbilityIDs;
		static std::vector<int>mUsingAbilities;


		
	};
}
