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
		mPs->SetTexture(material->GetTexture());
		mTr = GetComp<Transform>();
		mTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		mTr->SetScale(Vector3::One);

		mPs->InitializeParticles(100, Vector2::Zero, Vector2(10.0f, 10.0f), Vector4::One, Vector4::One, Vector4::One, 5.0f, 1.0f);
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