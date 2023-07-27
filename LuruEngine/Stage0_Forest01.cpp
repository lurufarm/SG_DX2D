#include "Stage0_Forest01.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgRenderer.h"
#include "..\Engine_SOURCE\sgCollisionManager.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgCamera.h"
#include "SCRIPT_MainCamera.h"

#include "Img_Stage0_Forest01_Map.h"
#include "Gobj_Player.h"
#include "Melee_SlimeA.h"

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
		Melee_SlimeA* slimea = object::Instantiate<Melee_SlimeA>(Vector3(50.0f, 50.0f, -0.1f), eLayerType::Monster, this);
		GameObject* Forest01camera = object::Instantiate<GameObject>(cameraPos, eLayerType::BGImg, this);
		mCamera = Forest01camera->AddComp<Camera>();
		Forest01camera->AddComp<SCRIPT_MainCamera>();

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
		renderer::mainCamera = mCamera;
		AddGameObj(eLayerType::Player, Player);

		CollisionManager::SetLayer(eLayerType::Player_Bullet, eLayerType::Monster, true);
	}
	void Stage0_Forest01::OnExit()
	{
	}
}