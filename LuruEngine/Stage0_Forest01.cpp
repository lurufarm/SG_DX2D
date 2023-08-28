#include "Stage0_Forest01.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgRenderer.h"
#include "..\Engine_SOURCE\sgCollisionManager.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgCamera.h"

#include "Tile_TilePalette.h"
#include "SCRIPT_MainCamera.h"
#include "Img_Stage0_Forest01_Map.h"
#include "Img_Crack.h"
#include "Gobj_Player.h"
#include "Monsters.h"
#include "UI_FocusBoxes2.h"
#include "Interact_Gate.h"

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

		mCrackPos[0] = Vector3(-300.0f, 200.0f, -0.1f);
		mCrackPos[1] = Vector3(-100.0f, -20.0f, -0.1f);
		mCrackPos[2] = Vector3(50.0f, 100.0f, -0.1f);

		Img_Crack* crack0 = object::Instantiate<Img_Crack>(mCrackPos[0], eLayerType::BGImg, this);
		Img_Crack* crack1 = object::Instantiate<Img_Crack>(mCrackPos[1], eLayerType::BGImg, this);
		Img_Crack* crack2 = object::Instantiate<Img_Crack>(mCrackPos[2], eLayerType::BGImg, this);

		mGate0 = object::Instantiate<Interact_Gate>(0, Vector3(-210.0f, 380.0f, -0.1f), eLayerType::InteractableObject, this);
		mGate1 = object::Instantiate<Interact_Gate>(0, Vector3(-173.0f, 380.0f, -0.1f), eLayerType::InteractableObject, this);
		mGate2 = object::Instantiate<Interact_Gate>(0, Vector3(-136.0f, 380.0f, -0.1f), eLayerType::InteractableObject, this);

		mGate0->SetNextScene(L"04_Stage0_Forest02");
		mGate1->SetNextScene(L"04_Stage0_Forest02");
		mGate2->SetNextScene(L"04_Stage0_Forest02");

#pragma region Monsters
		object::Instantiate<Melee_SlimeA>(eLayerType::Monster, this);
		object::Instantiate<Melee_SlimeA>(eLayerType::Monster, this);
		object::Instantiate<Melee_SlimeA>(eLayerType::Monster, this);
		object::Instantiate<Melee_SlimeA>(eLayerType::Monster, this);
		object::Instantiate<Melee_SlimeA>(eLayerType::Monster, this);
		object::Instantiate<Melee_SlimeA>(eLayerType::Monster, this);
		object::Instantiate<Melee_SlimeA>(eLayerType::Monster, this);
		object::Instantiate<Melee_SlimeA>(eLayerType::Monster, this);
		object::Instantiate<Melee_SlimeA>(eLayerType::Monster, this);
		object::Instantiate<Melee_SlimeA>(eLayerType::Monster, this);
		object::Instantiate<Melee_SlimeB>(eLayerType::Monster, this);
		object::Instantiate<Melee_SlimeB>(eLayerType::Monster, this);
		object::Instantiate<Melee_SlimeB>(eLayerType::Monster, this);
		object::Instantiate<Melee_SlimeB>(eLayerType::Monster, this);
		object::Instantiate<Melee_SlimeB>(eLayerType::Monster, this);
		object::Instantiate<Melee_Larva>(eLayerType::Monster, this);
		object::Instantiate<Melee_Larva>(eLayerType::Monster, this);
		object::Instantiate<Melee_Larva>(eLayerType::Monster, this);
		object::Instantiate<Melee_Larva>(eLayerType::Monster, this);
		object::Instantiate<Melee_Larva>(eLayerType::Monster, this);
		object::Instantiate<Melee_Cannibals>(eLayerType::Monster, this);
		object::Instantiate<Melee_Cannibals>(eLayerType::Monster, this);
		object::Instantiate<Melee_Cannibals>(eLayerType::Monster, this);
		object::Instantiate<Melee_Cannibals>(eLayerType::Monster, this);
		object::Instantiate<Melee_Cannibals>(eLayerType::Monster, this);
#pragma endregion

		//GameObject* mLight = new GameObject();
		//Light* mLg = mLight->AddComp<Light>();
		//AddGameObj(eLayerType::Light, mLight);
		//mLg->SetType(eLightType::Directional);
		//mLg->SetColor(mDayLight);

		PlayScene::Initialize();

	}
	void Stage0_Forest01::Update()
	{
		PlayScene::Update();
	}
	void Stage0_Forest01::LateUpdate()
	{
		PlayScene::LateUpdate();
	}
	void Stage0_Forest01::Render()
	{
		PlayScene::Render();
	}
	void Stage0_Forest01::OnEnter()
	{
		renderer::mainCamera = mCamera;

		PlayScene::OnEnter();

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


		CollisionManager::SetLayer(eLayerType::Player_Bullet, eLayerType::Monster, true);

		const std::wstring path0 = { L"..\\Resources\\Tile\\forestfd01_01" };
		TilePalette::AutoLoad(path0);

		//Player->GetComp<Collider2D>()->SetCenter(Vector2(100.0f, 100.0f));


	}
	void Stage0_Forest01::OnExit()
	{
		mFocus->DeleteSelectobj(mGate0);
		mFocus->DeleteSelectobj(mGate1);
		mFocus->DeleteSelectobj(mGate2);
		PlayScene::OnExit();
	}
}