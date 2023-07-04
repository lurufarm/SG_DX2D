#pragma once
#include "sgGameObject.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgMeshRenderer.h"
#include "sgMesh.h"
#include "sgMaterial.h"

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

	private:
	};
}
