#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgResources.h"
#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgMeshRenderer.h"

namespace sg
{
	class Gobj_Grid : public GameObject
	{
	public:
		Gobj_Grid();
		~Gobj_Grid();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		Transform* mTr = this->GetComp<Transform>();
		MeshRenderer* mMr = this->AddComp<MeshRenderer>();
	};
}

