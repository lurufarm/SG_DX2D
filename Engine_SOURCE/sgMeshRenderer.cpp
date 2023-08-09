#include "sgMeshRenderer.h"
#include "sgGameObject.h"
#include "sgTransform.h"
#include "sgRenderer.h"
#include "sgTime.h"
#include "sgAnimator.h"
#include "sgConstantBuffer.h"
#include "..\LuruEngine\Tile_TilePalette.h"

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

		if (mMaterial == Resources::Find<Material>(L"AnimationMaterial") || mMaterial == Resources::Find<Material>(L"AnimationMaterial2"))
		{
			Animator* at = GetOwner()->GetComp<Animator>();
			Vector2 spritescale = at->GetAnimationScale();
			mScale = Vector3(spritescale.x, spritescale.y, 1.0f) * originscale;

			tr->SetScale(mScale);
		}
		else
		{

			if (mMaterial != nullptr)
			{
				Vector3 imagescale = Vector3(mMaterial->GetTexture()->GetWidth(), mMaterial->GetTexture()->GetHeight(), 1.0f);
				mScale = originscale * imagescale;
			}
			else
			{
				mScale = originscale;
			}

			tr->SetScale(mScale);
		}

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
		Time::BindConstantBuffer();
		BindConstantBuffer();

		Animator* animator = GetOwner()->GetComp<Animator>();
		if (animator)
		{
			animator->Binds();
		}

		// Input assembler 정점 데이터 정보 지정
		mMesh->BindBuffer();
		// Bind VS, PS
		mMaterial->Binds();


		// Draw Render Target
		mMesh->Render();

		mMaterial->Clear();
	}

	void MeshRenderer::BindConstantBuffer()
	{
		renderer::TransparentCB TpCB = {};
		TpCB.alphaValue = GetOwner()->GetTransparent();
		//TpCB.TileIndex = sg::TilePalette::GetIndex();
		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Transparent];
		cb->SetData(&TpCB);
		cb->Bind(eShaderStage::PS);
		
	}
}