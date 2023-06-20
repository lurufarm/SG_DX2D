#include "sgMeshRenderer.h"
#include "sgGameObject.h"
#include "sgTransform.h"
#include "sgRenderer.h"

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
		tr->BindConstantBuffer();

		// Input assembler 정점 데이터 정보 지정
		mMesh->BindBuffer();
		// Bind VS, PS
		mMaterial->Binds();
		// Draw Render Target
		mMesh->Render();
	}
}