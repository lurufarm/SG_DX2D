#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgMeshRenderer.h"
#include "..\Engine_SOURCE\sgCollider2D.h"
#include "Gobj_Player.h"

namespace sg
{
	class Gobj_MobProjectile : public GameObject
	{
	public:
		Gobj_MobProjectile();
		~Gobj_MobProjectile();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		Vector3 GetLastPos() { return mLastPos; }
		Vector3 GetFirstPos() { return mFirstPos; }

		void SetProjOwner(Gobj_Monster* owner) { mProjOwner = owner; }
		Gobj_Monster* GetProjOwner() { return mProjOwner; }

		eMProjType GetProjType() { return mType; }

		void SetFirstPos(Vector3 pos) { mFirstPos = pos; }
		void SetLastPos(Vector3 pos) { mLastPos = pos; }

	protected:
		eMProjType mType;

		Transform* mTr = GetComp<Transform>();
		MeshRenderer* mMr = GetComp<MeshRenderer>();
		Collider2D* mCol = GetComp<Collider2D>();

		Vector3 mLastPos;
		Vector3 mFirstPos;
		Gobj_Monster* mProjOwner;

	private:
	};
}
