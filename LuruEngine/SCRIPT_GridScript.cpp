#include "SCRIPT_GridScript.h"

#include "../Engine_SOURCE/sgApplication.h"
#include "../Engine_SOURCE/sgRenderer.h"
#include "../Engine_SOURCE/sgConstantBuffer.h"
#include "../Engine_SOURCE/sgGameObject.h"
#include "../Engine_SOURCE/sgTransform.h"

extern sg::Application application;

namespace sg
{
	SCRIPT_GridScript::SCRIPT_GridScript()
		: mCamera(nullptr)
	{
	}
	SCRIPT_GridScript::~SCRIPT_GridScript()
	{
	}
	void SCRIPT_GridScript::Initialize()
	{
	}
	void SCRIPT_GridScript::Update()
	{
		if (mCamera == nullptr)
			return;

		GameObject* gameObj = mCamera->GetOwner();
		
		Transform* tr = gameObj->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();

		float scale = mCamera->GetSize();

		HWND hWnd = application.GetHwnd();
		RECT winRect = {};
		GetClientRect(hWnd, &winRect);

		float width = winRect.right - winRect.left;
		float height = winRect.bottom - winRect.top;
		Vector2 resolution(width, height);

		//Constant buffer
		graphics::ConstantBuffer* cb
			= renderer::constantBuffer[(int)eCBType::Grid];

		renderer::GridCB data;
		data.CameraPosition = Vector4(pos.x, pos.y, pos.z, 1.0f);
		data.Resolution = resolution;
		data.CameraScale = Vector2(scale, scale);

		cb->SetData(&data);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}
	void SCRIPT_GridScript::LateUpdate()
	{
	}
	void SCRIPT_GridScript::Render()
	{
	}
}