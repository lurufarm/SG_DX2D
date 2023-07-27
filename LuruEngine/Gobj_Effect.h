#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgAnimator.h"

namespace sg
{
	class Gobj_Effect : public GameObject
	{
	public:
		Gobj_Effect();
		~Gobj_Effect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;	

	protected:
		Transform* mTr;
		MeshRenderer* mMr;
		Collider2D* mCol;
		Animator* mAni;

		std::shared_ptr<Texture>mAtlas;
	};
}
