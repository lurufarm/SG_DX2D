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

		// Input assembler ���� ������ ���� ����
		renderer::mesh->BindBuffer();

		// Bind VS, PS
		renderer::shader->Binds();

		// Draw Render Target
		GetDevice()->DrawIndexed(renderer::mesh->GetIndexCount(), 0, 0);
	}
}