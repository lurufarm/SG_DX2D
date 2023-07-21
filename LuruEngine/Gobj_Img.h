#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgResources.h"
#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgMeshRenderer.h"
#include "..\Engine_SOURCE\sgMesh.h"
#include "..\Engine_SOURCE\sgMaterial.h"

namespace sg
{
	class Gobj_Img : public GameObject
	{
	public:
		Gobj_Img();
		~Gobj_Img();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();


		template <typename T>
		std::shared_ptr<T> GetMesh() { return this->GetComp<MeshRenderer>()->GetMesh(); }
		template <typename T>
		std::shared_ptr<T> GetMaterial() { return this->GetComp<MeshRenderer>()->GetMaterial(); }

	protected:
		Transform* mTr;
		MeshRenderer* mMr;

	private:
	};
}
