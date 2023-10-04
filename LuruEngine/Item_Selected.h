#pragma once
#include "Gobj_Item.h"

namespace sg
{
	class Item_Selected : public Gobj_Item
	{
	public:
		Item_Selected();
		~Item_Selected();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		int GetItemID () { return mID; }

	private:
		class Collider2D* mCol;

		int mID;
		Vector3 mPos;
		float mTime;
		bool mGetFirstPos = false;
	};
}
