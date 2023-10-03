#include "sgLight.h"
#include "sgRenderer.h"
#include "sgSceneManager.h"
#include "sgGameObject.h"
#include "sgTransform.h"
#include "sgScene.h"

namespace sg
{
	int Light::mNum = 0;

	Light::Light()
		: Component(eComponentType::Light)
	{
		mNum++;
	}
	Light::~Light()
	{
	}
	void Light::Initialize()
	{
	}
	void Light::Update()
	{
		mScene = GetOwner()->GetMyScene();

		if (GetOwner()->GetState() != GameObject::eState::Active)
		{
			mOn = false;
		}
		else if (GetOwner()->GetState() == GameObject::eState::Active)
		{
			mOn = true;
		}

		if (mPlus == false && mOn)
		{
			mNum++;
			mPlus = true;
		}
		if (mPlus == true && mOn == false)
		{
			mNum--;
			mPlus = false;
		}
	}
	void Light::LateUpdate()
	{
		if (mScene != nullptr)
			renderer::lights.insert(std::make_pair(mScene->GetName(), this));
		Transform* tr = GetOwner()->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();
		mAttribute.position = Vector4(pos.x, pos.y, pos.z, 1.0f);
		mAttribute.direction = Vector4(tr->Forward().x, tr->Forward().y, tr->Forward().z, 1.0f);
		mAttribute.pad = mNum;
	}
	void Light::Render()
	{
	}
}