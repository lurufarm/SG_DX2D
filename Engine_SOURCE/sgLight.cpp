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
		, mLightPos(Vector3::Zero)
		, mLightColor(Vector4::Zero)
		, mOn(true)
	{
		//mNum++;
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
		if (mScene != nullptr && mOn)
			renderer::lights.insert(std::make_pair(mScene->GetName(), this));
		Transform* tr = GetOwner()->GetComp<Transform>();
		Vector3 pos = tr->GetPosition() + mLightPos;
		mAttribute.position = Vector4(pos.x, pos.y, pos.z, 1.0f);
		mAttribute.direction = Vector4(tr->Forward().x, tr->Forward().y, tr->Forward().z, 1.0f);
		mAttribute.color = mLightColor;
		//mAttribute.pad = mNum;
	}
	void Light::Render()
	{
	}
}