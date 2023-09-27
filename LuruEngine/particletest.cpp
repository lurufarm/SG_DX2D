#include "particletest.h"
#include "sgResources.h"
#include "sgMaterial.h"
#include "sgParticleSystem.h"
#include "sgMeshRenderer.h"
#include "sgTime.h"

namespace sg
{
	void particletest::Initialize()
	{
		SetName(L"testparticle");
		mPs = AddComp<ParticleSystem>();
		mPs->SetOwner(this);
		std::shared_ptr<Material> material = Resources::Find<Material>(L"ParticleMaterial2");
		mPs->SetMaterial(material);
		mTr = GetComp<Transform>();
		mTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		mTr->SetScale(Vector3::One);
		Vector4 scolor = Vector4(0.3f, 1.0f, 0.2f, 1.0f);
		Vector4 mcolor = Vector4(1.0f, 0.3f, 0.2f, 0.8f);
		Vector4 ecolor = Vector4(1.0f, 1.0f, 1.0f, 0.2f);

		mPs->SetParticleOptions(100, Vector2(1.0f, 1.2f), 40.0f, scolor, ecolor, mcolor, 4.0f, 0.3f);
		mPs->Initialize();
	}
	void particletest::Update()
	{
		GameObject::Update();
	}
	void particletest::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void particletest::Render()
	{
		GameObject::Render();
	}
}