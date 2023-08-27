#include "Stage0_Forest04.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgRenderer.h"
#include "..\Engine_SOURCE\sgCollisionManager.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgCamera.h"

#include "Tile_TilePalette.h"
#include "SCRIPT_MainCamera.h"
#include "Img_Stage0_Forest01_Map.h"
#include "Gobj_Player.h"
#include "Monsters.h"
#include "Interact_Gate.h"
#include "UI_FocusBoxes2.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	Stage0_Forest04::Stage0_Forest04()
	{
		SetName(L"06_Stage0_Forest04");
	}
	Stage0_Forest04::~Stage0_Forest04()
	{
	}
	void Stage0_Forest04::Initialize()
	{
		Vector3 cameraPos = Vector3(0.0f, 0.0f, -10.0f);
		Vector3 pos = Vector3(-11.0f, 5.0f, 0.0f);
		object::Instantiate<Img_Stage0_Map>(Img_Stage0_Map::Stage0::forestfd04, pos, eLayerType::BGImg, this);

		GameObject* Forest04camera = object::Instantiate<GameObject>(cameraPos, eLayerType::BGImg, this);
		mCamera = Forest04camera->AddComp<Camera>();
		Forest04camera->AddComp<SCRIPT_MainCamera>();

		mGate0 = object::Instantiate<Interact_Gate>(0, Vector3(-82.0f, 430.0f, -0.1f), eLayerType::InteractableObject, this);
		mGate1 = object::Instantiate<Interact_Gate>(0, Vector3(-45.0f, 430.0f, -0.1f), eLayerType::InteractableObject, this);
		mGate2 = object::Instantiate<Interact_Gate>(0, Vector3(8.0, 430.0f, -0.1f), eLayerType::InteractableObject, this);

		mGate0->SetNextScene(L"02_LobbyScene");
		mGate1->SetNextScene(L"02_LobbyScene");
		mGate2->SetNextScene(L"02_LobbyScene");
		
		//GameObject* mLight = new GameObject();
		//Light* mLg = mLight->AddComp<Light>();
		//AddGameObj(eLayerType::Light, mLight);
		//mLg->SetType(eLightType::Directional);
		//mLg->SetColor(mDayLight);


		SCENE_Stage0::Initialize();
	}
	void Stage0_Forest04::Update()
	{
		SCENE_Stage0::Update();
	}
	void Stage0_Forest04::LateUpdate()
	{
		SCENE_Stage0::LateUpdate();
	}
	void Stage0_Forest04::Render()
	{
		SCENE_Stage0::Render();
	}
	void Stage0_Forest04::OnEnter()
	{
		renderer::mainCamera = mCamera;

		PlayScene::OnEnter();

		//Melee_SlimeA* slimea0 = object::Instantiate<Melee_SlimeA>(Vector3(100.0f, 100.0f, -0.1f), eLayerType::Monster, this);
		//Melee_SlimeA* slimea1 = object::Instantiate<Melee_SlimeA>(Vector3(-100.0f, 100.0f, -0.1f), eLayerType::Monster, this);

		//Melee_SlimeB* slimeb0 = object::Instantiate<Melee_SlimeB>(Vector3(200.0f, 200.0f, -0.1f), eLayerType::Monster, this);
		//Melee_SlimeB* slimeb1 = object::Instantiate<Melee_SlimeB>(Vector3(-200.0f, 200.0f, -0.1f), eLayerType::Monster, this);

		//Melee_Larva* larva0 = object::Instantiate<Melee_Larva>(Vector3(100.0f, 50.0f, -0.1f), eLayerType::Monster, this);
		//Melee_Larva* larva1 = object::Instantiate<Melee_Larva>(Vector3(-100.0f, 50.0f, -0.1f), eLayerType::Monster, this);

		//Melee_EliteLarva* Elarva0 = object::Instantiate<Melee_EliteLarva>(Vector3(80.0f, 50.0f, -0.1f), eLayerType::Monster, this);
		//Melee_EliteLarva* Elarva1 = object::Instantiate<Melee_EliteLarva>(Vector3(-80.0f, 50.0f, -0.1f), eLayerType::Monster, this);

		//Melee_Cannibals* cannibals0 = object::Instantiate<Melee_Cannibals>(Vector3(100.0f, 80.0f, -0.1f), eLayerType::Monster, this);
		//Melee_Cannibals* cannibals1 = object::Instantiate<Melee_Cannibals>(Vector3(-100.0f, 80.0f, -0.1f), eLayerType::Monster, this);

		//Melee_EliteCannibals* Ecannibals0 = object::Instantiate<Melee_EliteCannibals>(Vector3(80.0f, 80.0f, -0.1f), eLayerType::Monster, this);
		//Melee_EliteCannibals* Ecannibals1 = object::Instantiate<Melee_EliteCannibals>(Vector3(-80.0f, 80.0f, -0.1f), eLayerType::Monster, this);


		//Ranged_CannibalFlowerA* Cflowera0 = object::Instantiate<Ranged_CannibalFlowerA>(Vector3(50.0f, 80.0f, -0.1f), eLayerType::Monster, this);
		//Ranged_CannibalFlowerA* Cflowera1 = object::Instantiate<Ranged_CannibalFlowerA>(Vector3(-50.0f, 80.0f, -0.1f), eLayerType::Monster, this);

		//Ranged_Ent* ent0 = object::Instantiate<Ranged_Ent>(Vector3(100.0f, 100.0f, -0.1f), eLayerType::Monster, this);
		//Boss_OldEnt* bent = object::Instantiate<Boss_OldEnt>(Vector3(100.0f, 100.0f, -0.1f), eLayerType::Monster, this);



		const std::wstring path0 = { L"..\\Resources\\Tile\\forestfd04_00" };
		TilePalette::AutoLoad(path0);

		Player->GetComp<Transform>()->SetPosition(0.0f, 0.0f, 0.0f);

	}
	void Stage0_Forest04::OnExit()
	{
		PlayScene::OnExit();
		mFocus->DeleteSelectobj(mGate0);
		mFocus->DeleteSelectobj(mGate1);
		mFocus->DeleteSelectobj(mGate2);

	}
}