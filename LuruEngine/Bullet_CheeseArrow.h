#pragma once
#include "Gobj_Bullet.h"

namespace sg
{
	class Bullet_CheeseArrow : public Gobj_Bullet
	{
	public:
		Bullet_CheeseArrow();
		~Bullet_CheeseArrow();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
		
		Transform* mTr = GetComp<Transform>();
		MeshRenderer* mMr = GetComp<MeshRenderer>();
		Collider2D* mCol = GetComp<Collider2D>();

		GameObject* mTarget;
	};
}
