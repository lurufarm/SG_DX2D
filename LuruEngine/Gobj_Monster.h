#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"

namespace sg
{
	class Gobj_Monster : public GameObject
	{
	public:
		Gobj_Monster();
		~Gobj_Monster();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	protected:
		Transform* mTr;
		MeshRenderer* mMr;
		Collider2D* mCol;
		Animator* mAni;
		GameObject* mPlayer;
		bool mTargeted;

	private:

	};
}

