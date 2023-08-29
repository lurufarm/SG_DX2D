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
		Gobj_Bullet	();
		~Gobj_Bullet();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		Vector3 GetLastPos() { return mLastPos; }
		Vector3 GetFirstPos() { return mFirstPos; }

		void SetBulletOwner(Gobj_Character* owner) { mBulletOwner = owner; }
		Gobj_Character* GetBulletOwner() { return mBulletOwner; }

		eBulletType GetBulletType() { return mType; }
		int GetThisNum() { return mThisNum; }

	protected:
		eBulletType mType;
		GameObject* mTarget;

		Transform* mTr = GetComp<Transform>();
		MeshRenderer* mMr = GetComp<MeshRenderer>();
		Collider2D* mCol = GetComp<Collider2D>();

		Vector3 mLastPos;
		Vector3 mFirstPos;
		Gobj_Character* mBulletOwner;

		int mThisNum;


	private:
	};
}
