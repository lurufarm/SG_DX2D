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
	}
	void Light::LateUpdate()
	{
		renderer::lights.insert(std::make_pair(mScene, this));

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