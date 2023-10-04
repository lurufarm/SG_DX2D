#include "Stage0_Forest07.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgRenderer.h"
#include "..\Engine_SOURCE\sgCollisionManager.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgCamera.h"

#include "Tile_TilePalette.h"
#include "SCRIPT_MainCamera.h"
#include "Img_Stage0_Forest01_Map.h"
#include "Img_Crack.h"
#include "Img_Torch.h"
#include "Img_StartingPlate.h"
#include "Img_RewardPlate.h"
#include "Gobj_Player.h"
#include "Monsters.h"
#include "Interact_Gate.h"
#include "UI_FocusBoxes2.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	Stage0_Forest07::Stage0_Forest07()
	{
		SetName(L"09_Stage0_Forest07");
	}
	Stage0_Forest07::~Stage0_Forest07()
	{
	}
	void Stage0_Forest07::Initialize()
	{
		Vector3 cameraPos = Vector3(0.0f, 0.0f, -10.0f);
		Vector3 pos = Vector3(0.0f, -3.0f, 0.0f);
		mCrackPos[0] = Vector3(-150.0f, 45.0f, -0.5f);
		mCrackPos[1] = Vector3(-165.0f, -190.0f, -0.5f);
		mCrackPos[2] = Vector3(165.0f, -185.0f, -0.5f);
		mStartPos = Vector3(135, 85.0f, -1.0f);
		mGatePos[0] = Vector3(-82.0f, 390.0f, -0.1f);
		mGatePos[1] = Vector3(-45.0f, 390.0f, -0.1f);
		mGatePos[2] = Vector3(-8.0, 390.0f, -0.1f);

		mRewardPos = mGatePos[1];
		mRewardPos.y -= 80.0f;

		object::Instantiate<Img_Stage0_Map>(Img_Stage0_Map::Stage0::forestdg03, pos, eLayerType::BGImg, this);
		object::Instantiate<Img_StartingPlate>(mStartPos, eLayerType::BGImg, this);

		GameObject* Forest07camera = object::Instantiate<GameObject>(cameraPos, eLayerType::BGImg, this);
		mCamera = Forest07camera->AddComp<Camera>();
		Forest07camera->AddComp<SCRIPT_MainCamera>();

		object::Instantiate<Img_Torch>(Vector3(5, -60, -0.1f), eLayerType::BGImg, this);
		object::Instantiate<Img_Torch>(Vector3(-205, 180, -0.1f), eLayerType::BGImg, this);
		object::Instantiate<Img_Torch>(Vector3(-295, -210, -0.1f), eLayerType::BGImg, this);
		object::Instantiate<Img_Torch>(Vector3(-120, -310, -0.1f), eLayerType::BGImg, this);
		object::Instantiate<Img_Torch>(Vector3(185, 180, -0.1f), eLayerType::BGImg, this);


		mCrack0 = object::Instantiate<Img_Crack>(mCrackPos[0], eLayerType::BGImg, this);
		mCrack1 = object::Instantiate<Img_Crack>(mCrackPos[1], eLayerType::BGImg, this);
		mCrack2 = object::Instantiate<Img_Crack>(mCrackPos[2], eLayerType::BGImg, this);

		object::Instantiate<Img_RewardPlate>(mRewardPos, eLayerType::BGImg, this);

		mGate0 = object::Instantiate<Interact_Gate>(0, mGatePos[0], eLayerType::InteractableObject, this);
		mGate1 = object::Instantiate<Interact_Gate>(0, mGatePos[1], eLayerType::InteractableObject, this);
		mGate2 = object::Instantiate<Interact_Gate>(0, mGatePos[2], eLayerType::InteractableObject, this);

		mGate0->SetNextScene(L"10_Stage0_Forest08");
		mGate1->SetNextScene(L"10_Stage0_Forest08");
		mGate2->SetNextScene(L"10_Stage0_Forest08");

#pragma region Monsters
		//object::Instantiate<Melee_SlimeB>(eLayerType::Monster, this);
		//object::Instantiate<Melee_SlimeB>(eLayerType::Monster, this);
		//object::Instantiate<Melee_SlimeB>(eLayerType::Monster, this);
		//object::Instantiate<Melee_SlimeB>(eLayerType::Monster, this);
		//object::Instantiate<Melee_SlimeB>(eLayerType::Monster, this);
		//object::Instantiate<Melee_Larva>(eLayerType::Monster, this);
		//object::Instantiate<Melee_Larva>(eLayerType::Monster, this);
		//object::Instantiate<Melee_Larva>(eLayerType::Monster, this);
		//object::Instantiate<Melee_Larva>(eLayerType::Monster, this);
		//object::Instantiate<Melee_Larva>(eLayerType::Monster, this);
		//object::Instantiate<Melee_Cannibals>(eLayerType::Monster, this);
		//object::Instantiate<Melee_Cannibals>(eLayerType::Monster, this);
		//object::Instantiate<Melee_Cannibals>(eLayerType::Monster, this);
		//object::Instantiate<Ranged_CannibalFlowerA>(eLayerType::Monster, this);
		//object::Instantiate<Ranged_CannibalFlowerA>(eLayerType::Monster, this);
		//object::Instantiate<Ranged_CannibalFlowerA>(eLayerType::Monster, this);
		//object::Instantiate<Ranged_Ent>(eLayerType::Monster, this);
		//object::Instantiate<Ranged_Ent>(eLayerType::Monster, this);
		//object::Instantiate<Ranged_Ent>(eLayerType::Monster, this);
		//object::Instantiate<Boss_OldEnt>(eLayerType::Monster, this);
#pragma endregion

		PlayScene2::Initialize();
	}
	void Stage0_Forest07::Update()
	{
		PlayScene2::Update();
	}
	void Stage0_Forest07::LateUpdate()
	{
		PlayScene2::LateUpdate();
	}
	void Stage0_Forest07::Render()
	{
		PlayScene2::Render();
	}
	void Stage0_Forest07::OnEnter()
	{
		renderer::mainCamera = mCamera;

		PlayScene2::OnEnter();

		const std::wstring path0 = { L"..\\Resources\\Tile\\forestdg03_00" };
		TilePalette::AutoLoad(path0);
	}
	void Stage0_Forest07::OnExit()
	{
		PlayScene2::OnExit();
		mFocus->DeleteSelectobj(mGate0);
		mFocus->DeleteSelectobj(mGate1);
		mFocus->DeleteSelectobj(mGate2);

	}
}