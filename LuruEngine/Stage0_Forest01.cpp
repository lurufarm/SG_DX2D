#include "Stage0_Forest01.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgRenderer.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgCamera.h"

#include "SCRIPT_CameraScript.h"

#include "Img_Stage0_Forest01_Map.h"
#include "Gobj_Player.h"

extern sg::Gobj_Player* Player;

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
		mCamera = Forest01camera->AddComp<Camera>();
		SCRIPT_CameraScript* cameracomp1 = Forest01camera->AddComp<SCRIPT_CameraScript>();
		//renderer::mainCamera = cameraComp;

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
		AddGameObj(eLayerType::Player, Player);
		float BgColor[3] = { 0.5f, 0.5f, 0.5f };
		GetDevice()->SetBgColor(BgColor);
		renderer::mainCamera = mCamera;
		renderer::cameras.push_back(mCamera);

	}
	void Stage0_Forest01::OnExit()
	{
	}
}