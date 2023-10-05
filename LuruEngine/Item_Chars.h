#pragma once
#include "Gobj_Item.h"

namespace sg
{
	class Item_Chars : public Gobj_Item
	{
	public:
		Item_Chars(int num);
		~Item_Chars();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void DeleteinCharIDs(int a);
		void DeleteinUsingChars(int a);

		int RandomNumber();

	private:

		static UINT mItemSpawnCount[10];
		static std::vector<int>mCharIDs;
		static std::vector<int>mUsingCharIDs;
	};
}
