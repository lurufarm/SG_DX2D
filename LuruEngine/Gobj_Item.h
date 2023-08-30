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

	protected:
		Transform* mTr;
		MeshRenderer* mMr;
		Collider2D* mCol;
		Animator* mAni;
		Gobj_Player* mPlayer;

	private:
	};
}
