#include "Stage0_Forest01.h"
#include "..\Engine_SOURCE\sgRenderer.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgCamera.h"

#include "SCRIPT_CameraScript.h"

#include "Img_Stage0_Forest01_Map.h"

namespace sg
{
	Stage0_Forest01::Stage0_Forest01()
	{
	}
	Stage0_Forest01::~Stage0_Forest01()
	{
	}
	void Stage0_Forest01::Initialize()
	{
		Vector3 cameraPos = Vector3(0.0f, 0.0f, -10.0f);

		Img_Stage0_Forest01_Map* map = object::Instantiate<Img_Stage0_Forest01_Map>(Img_Stage0_Forest01_Map::ForestFd::forest01, eLayerType::BGImg, this);

		GameObject* Forest01camera = object::Instantiate<GameObject>(cameraPos, eLayerType::BGImg, this);
		Camera* cameraComp = Forest01camera->AddComp<Camera>();
		SCRIPT_CameraScript* cameracomp1 = Forest01camera->AddComp<SCRIPT_CameraScript>();
		//cameraComp->EnableLayerMask();
		renderer::cameras.push_back(cameraComp);

		SCENE_Stage0::Initialize();
	}
	void Stage0_Forest01::Update()
	{
		SCENE_Stage0::Update();
	}
	void Stage0_Forest01::LateUpdate()
	{
		SCENE_Stage0::LateUpdate();
	}
	void Stage0_Forest01::Render()
	{
		SCENE_Stage0::Render();
	}
	void Stage0_Forest01::OnEnter()
	{
		float BgColor[3] = { 0.5f, 0.5f, 0.5f };
		GetDevice()->SetBgColor(BgColor);
	}
	void Stage0_Forest01::OnExit()
	{
	}
}