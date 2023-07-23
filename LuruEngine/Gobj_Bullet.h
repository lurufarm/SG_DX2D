#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgMeshRenderer.h"
#include "..\Engine_SOURCE\sgCollider2D.h"
#include "Gobj_Player.h"

namespace sg
{
	class Gobj_Bullet : public GameObject
	{
	public:
		Gobj_Bullet();
		~Gobj_Bullet();

		virtual void initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		Vector3 GetTargetPos() { return mTargetPos; }
		Vector3 GetFirstPos() { return mFirstPos; }

		virtual void SetOwner(Gobj_Player* owner) { mOwner = owner; }
		GameObject* GetOwner() { return mOwner; }

	protected:
		eBulletType mType;
		Vector3 mTargetPos;
		Vector3 mFirstPos;
		GameObject* mTarget;
		Gobj_Player* mOwner;


	private:
	};
}
