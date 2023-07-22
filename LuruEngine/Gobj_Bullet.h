#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgMeshRenderer.h"
#include "..\Engine_SOURCE\sgCollider2D.h"

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

	protected:
		eBulletType mType;

	private:
	};
}
