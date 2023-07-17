#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgResources.h"
#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgMeshRenderer.h"
#include "..\Engine_SOURCE\sgCollider2D.h"
#include "..\Engine_SOURCE\sgMesh.h"
#include "..\Engine_SOURCE\sgMaterial.h"


namespace sg
{
	class Gobj_Interactable : public GameObject
	{
	public:
		Gobj_Interactable();
		~Gobj_Interactable();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void SetMesh()
		{
			this->GetComp<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		}
		virtual void SetMaterial(const std::wstring& key)
		{
			this->GetComp<MeshRenderer>()->SetMaterial(Resources::Find<Material>(key));
		}

		template <typename T>
		std::shared_ptr<T> GetMesh() { return this->GetComp<MeshRenderer>()->GetMesh(); }
		template <typename T>
		std::shared_ptr<T> GetMaterial() { return this->GetComp<MeshRenderer>()->GetMaterial(); }

	protected:
		Transform* mTr;
		MeshRenderer* mMr;
		Collider2D* mCol;
	private:
	};
}