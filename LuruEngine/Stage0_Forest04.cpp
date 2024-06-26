#include "Stage0_Forest04.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgRenderer.h"
#include "..\Engine_SOURCE\sgCollisionManager.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgCamera.h"

#include "Tile_TilePalette.h"
#include "SCRIPT_MainCamera.h"
#include "Img_Stage0_Forest01_Map.h"
#include "Img_Crack.h"
#include "Img_StartingPlate.h"
#include "Img_RewardPlate.h"
#include "Gobj_Player.h"
#include "Monsters.h"
#include "Interact_Gate.h"
#include "UI_FocusBoxes2.h"
#include "Gobj_Sound.h"
#include "Stage0_Forest01.h"

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
		mCrackPos[0] = Vector3(165.0f, -180.0f, -0.5f);
		mCrackPos[1] = Vector3(0.0f, -55.0f, -0.5f);
		mCrackPos[2] = Vector3(-15.0f, 240.0f, -0.5f);
		mStartPos = Vector3(-75.0f, -310.0f, -1.0f);
		mGatePos[0] = Vector3(-82.0f, 430.0f, -0.1f);
		mGatePos[1] = Vector3(-45.0f, 430.0f, -0.1f);
		mGatePos[2] = Vector3(-8.0, 430.0f, -0.1f);

		mRewardPos = mGatePos[1];
		mRewardPos.y -= 80.0f;

		object::Instantiate<Img_Stage0_Map>(Img_Stage0_Map::Stage0::forestfd04, pos, eLayerType::BG, this);
		object::Instantiate<Img_StartingPlate>(mStartPos, eLayerType::BG, this);

		GameObject* Forest04camera = object::Instantiate<GameObject>(cameraPos, eLayerType::BG, this);
		mCamera = Forest04camera->AddComp<Camera>();
		Forest04camera->AddComp<SCRIPT_MainCamera>();

		Img_Crack* crack0 = object::Instantiate<Img_Crack>(mCrackPos[0], eLayerType::BG, this);
		Img_Crack* crack1 = object::Instantiate<Img_Crack>(mCrackPos[1], eLayerType::BG, this);
		Img_Crack* crack2 = object::Instantiate<Img_Crack>(mCrackPos[2], eLayerType::BG, this);

		object::Instantiate<Img_RewardPlate>(mRewardPos, eLayerType::BG, this);

		mGate0 = object::Instantiate<Interact_Gate>(0, mGatePos[0], eLayerType::InteractableObject, this);
		mGate1 = object::Instantiate<Interact_Gate>(0, mGatePos[1], eLayerType::InteractableObject, this);
		mGate2 = object::Instantiate<Interact_Gate>(0, mGatePos[2], eLayerType::InteractableObject, this);

		mGate0->SetNextScene(L"07_Stage0_Forest05");
		mGate1->SetNextScene(L"07_Stage0_Forest05");
		mGate2->SetNextScene(L"07_Stage0_Forest05");

#pragma region Monsters
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
		object::Instantiate<Ranged_CannibalFlowerA>(eLayerType::Monster, this);
		object::Instantiate<Ranged_CannibalFlowerA>(eLayerType::Monster, this);
		object::Instantiate<Ranged_CannibalFlowerA>(eLayerType::Monster, this);
		object::Instantiate<Ranged_Ent>(eLayerType::Monster, this);
		object::Instantiate<Ranged_Ent>(eLayerType::Monster, this);
		object::Instantiate<Ranged_Ent>(eLayerType::Monster, this);
		object::Instantiate<Boss_OldEnt>(eLayerType::Monster, this);
#pragma endregion
		
		PlayScene::Initialize();
	}
	void Stage0_Forest04::Update()
	{
		PlayScene::Update();
	}
	void Stage0_Forest04::LateUpdate()
	{
		PlayScene::LateUpdate();
	}
	void Stage0_Forest04::Render()
	{
		PlayScene::Render();
	}
	void Stage0_Forest04::OnEnter()
	{
		renderer::mainCamera = mCamera;

		PlayScene::OnEnter();

		const std::wstring path0 = { L"..\\Resources\\Tile\\forestfd04_00" };
		TilePalette::AutoLoad(path0);

	}
	void Stage0_Forest04::OnExit()
	{
		PlayScene::OnExit();
		mFocus->DeleteSelectobj(mGate0);
		mFocus->DeleteSelectobj(mGate1);
		mFocus->DeleteSelectobj(mGate2);

		//Gobj_Sound* bgm = dynamic_cast<Stage0_Forest01*>(SceneManager::FindScene(L"03_Stage0_Forest01"))->GetForestFDBGM();
		//bgm->Stop();

	}
}