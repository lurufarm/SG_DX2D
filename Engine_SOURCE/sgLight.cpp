#include "sgLight.h"
#include "sgRenderer.h"
#include "sgGameObject.h"
#include "sgTransform.h"

namespace sg
{
	Light::Light()
		:Component(eComponentType::Light)
	{
	}
	Light::~Light()
	{
	}
	void Light::Initialize()
	{
	}
	void Light::Update()
	{
	}
	void Light::LateUpdate()
	{
		renderer::lights.push_back(this);

		Transform* tr = GetOwner()->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();
		mAttribute.position = Vector4(pos.x, pos.y, pos.z, 1.0f);
		mAttribute.direction = Vector4(tr->Forward().x, tr->Forward().y, tr->Forward().z, 1.0f);
	}
	void Light::Render()
	{
	}
}