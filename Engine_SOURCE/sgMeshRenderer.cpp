#include "sgMeshRenderer.h"
#include "sgGameObject.h"
#include "sgTransform.h"
#include "sgRenderer.h"
#include "sgTime.h"

namespace sg
{
	MeshRenderer::MeshRenderer()
		: Component(eComponentType::MeshRenderer)
	{
	}
	MeshRenderer::~MeshRenderer()
	{
	}
	void MeshRenderer::Initialize()
	{
		Transform* tr = GetOwner()->GetComp<Transform>();
		Vector3 originscale = tr->GetScale();
		Vector3 imagescale = Vector3(mMaterial->GetTexture()->GetWidth() / 65, mMaterial->GetTexture()->GetHeight() / 65, 1.0f);
		mScale = originscale * imagescale;
	}
	void MeshRenderer::Update()
	{
	}
	void MeshRenderer::LateUpdate()
	{
	}
	void MeshRenderer::Render()
	{
		Transform* tr = GetOwner()->GetComp<Transform>();
		mScale = Vector3(200.0f, 200.0f, 1.0f);
		tr->SetScale(mScale);
		tr->BindConstantBuffer();
		Time::BindConstantBuffer();


		// Input assembler 정점 데이터 정보 지정
		mMesh->BindBuffer();
		// Bind VS, PS
		mMaterial->Binds();
		// Draw Render Target
		mMesh->Render();

		mMaterial->Clear();
	}
}