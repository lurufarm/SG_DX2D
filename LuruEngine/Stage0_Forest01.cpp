#include "Stage0_Forest01.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgRenderer.h"
#include "..\Engine_SOURCE\sgCollisionManager.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgCamera.h"

#include "Tile_TilePalette.h"
#include "SCRIPT_MainCamera.h"
#include "Img_Stage0_Forest01_Map.h"
#include "Gobj_Player.h"
#include "Melee_SlimeA.h"
#include "Melee_SlimeB.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	Stage0_Forest01::Stage0_Forest01()
	{
		SetName(L"03_Stage0_Forest01");
	}
	Stage0_Forest01::~Stage0_Forest01()
	{
	}
	void Stage0_Forest01::Initialize()
	{
		Vector3 cameraPos = Vector3(0.0f, 0.0f, -10.0f);

		Vector3 pos = Vector3(-11.0f, 5.0f, 0.0f);
		object::Instantiate<Img_Stage0_Map>(Img_Stage0_Map::Stage0::forestfd01, pos, eLayerType::BGImg, this);

		GameObject* Forest01camera = object::Instantiate<GameObject>(cameraPos, eLayerType::BGImg, this);
		mCamera = Forest01camera->AddComp<Camera>();
		Forest01camera->AddComp<SCRIPT_MainCamera>();

		//GameObject* mLight = new GameObject();
		//Light* mLg = mLight->AddComp<Light>();
		//AddGameObj(eLayerType::Light, mLight);
		//mLg->SetType(eLightType::Directional);
		//mLg->SetColor(mDayLight);


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

		Melee_SlimeA* slimea0 = object::Instantiate<Melee_SlimeA>(Vector3(100.0f, 100.0f, -0.1f), eLayerType::Monster, this);
		Melee_SlimeA* slimea1 = object::Instantiate<Melee_SlimeA>(Vector3(-100.0f, 100.0f, -0.1f), eLayerType::Monster, this);

		Melee_SlimeB* slimeb0 = object::Instantiate<Melee_SlimeB>(Vector3(200.0f, 200.0f, -0.1f), eLayerType::Monster, this);
		Melee_SlimeB* slimeb1 = object::Instantiate<Melee_SlimeB>(Vector3(-200.0f, 200.0f, -0.1f), eLayerType::Monster, this);

		CollisionManager::SetLayer(eLayerType::Player_Bullet, eLayerType::Monster, true);

		const std::wstring path0 = { L"..\\Resources\\Tile\\forestfd01_01" };
		TilePalette::AutoLoad(path0);

		PlayScene::OnEnter();

	}
	void Stage0_Forest01::OnExit()
	{
		PlayScene::OnExit();
	}
}