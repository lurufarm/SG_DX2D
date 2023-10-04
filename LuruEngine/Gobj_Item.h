#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"
#include "Gobj_Player.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	class Gobj_Item : public GameObject
	{
	public:
		Gobj_Item();
		~Gobj_Item();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		virtual UINT RandomNumber(int a, int b);

		void SetItemID(int a) { mItemID = a; }
		int GetItemID() { return mItemID; }

		void SetItemActivate(bool value) { mActivate = value; }

	protected:
		Transform* mTr;
		MeshRenderer* mMr;
		Animator* mAni;
		Gobj_Player* mPlayer;

		int mItemID;
		bool mActivate;

	private:
	};
}
