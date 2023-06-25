#pragma once
#include "sgGameObject.h"
#include "sgTransform.h"
#include "sgResources.h"
#include "sgMeshRenderer.h"
#include "sgMesh.h"
#include "sgMaterial.h"

namespace sg
{
	class Gobj_BGImg : public GameObject
	{
	public:
		Gobj_BGImg();
		~Gobj_BGImg();

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
		eLayerType mLayer;
		Transform* mTr;
		MeshRenderer* mMr;

	private:
	};
}
