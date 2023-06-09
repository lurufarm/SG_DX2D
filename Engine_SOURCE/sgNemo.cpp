#include "sgNemo.h"
#include "sgMesh.h"
#include "sgShader.h"
#include "sgRenderer.h"
#include "sgGraphicDevice_Dx11.h"

#include "sgInput.h"
#include "sgTime.h"

#include <random>


namespace sg
{
	using namespace renderer;

	Nemo::Nemo()
		: mState(eState::Active)
		, mStat{}
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		float color[3] = {};
		for (size_t i = 0; i < 3; i++)
		{
			std::uniform_real_distribution<float> randomcolor(0.0f, 1.0f);
			color[i] = randomcolor(gen);
		}
		SetStat(30.0f, Vector3(0.0f, 0.0f, 0.0f), Vector4(color[0], color[1], color[2], 1.0f));

	}
	Nemo::~Nemo()
	{
	}
	void Nemo::Initialize()
	{		
		GameObject::Initialize();
	}
	void Nemo::Update()
	{
		GameObject::Update();

		Vector3 pos = GetStat().mPos;

		if (Input::KeyP(eKeyCode::W) || Input::KeyD(eKeyCode::W))
		{
			pos.y += 100.0f * Time::DeltaTime();
		}
		else if (Input::KeyP(eKeyCode::S) || Input::KeyD(eKeyCode::S))
		{
			pos.y -= 100.0f * Time::DeltaTime();
		}
		if (Input::KeyP(eKeyCode::A) || Input::KeyD(eKeyCode::A))
		{
			pos.x -= 100.0f * Time::DeltaTime();
		}
		else if (Input::KeyP(eKeyCode::D) || Input::KeyD(eKeyCode::D))
		{
			pos.x += 100.0f * Time::DeltaTime();
		}

		SetStat(mStat.mScale, pos, mStat.mColor);


	}
	void Nemo::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Nemo::Render()
	{
		renderer::constantBuffer->SetData(&mStat);
		renderer::constantBuffer->Bind(eShaderStage::VS);

		renderer::mesh->BindBuffer();
		renderer::shader->Binds();
		graphics::GetDevice()->DrawIndexed(renderer::mesh->GetIndexCount(), 0, 0);

		GameObject::Render();
	}
}