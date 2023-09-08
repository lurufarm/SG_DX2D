#pragma once
#include "..\Engine_SOURCE\sgScript.h"
#include "Gobj_Item.h"
#include "Item_Selected.h"

namespace sg
{
	class SCRIPT_Item : public Script
	{
	public:
		SCRIPT_Item();
		~SCRIPT_Item();

		void Initialize();
		void Update();

		void OnCollisionEnter(Collider2D* other);

	private:

		Item_Selected* mOwner;
		Gobj_Player* mPlayer;

	};

}