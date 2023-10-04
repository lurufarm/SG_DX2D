#include "Stage0_Forest03.h"
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

extern sg::Gobj_Player* Player;

namespace sg
{
	Stage0_Forest03::Stage0_Forest03()
	{
		SetName(L"05_Stage0_Forest03");
	}
	Stage0_Forest03::~Stage0_Forest03()
	{
	}
	void Stage0_Forest03::Initialize()
	{
		Vector3 cameraPos = Vector3(0.0f, 0.0f, -10.0f);
		Vector3 pos = Vector3(-11.0f, -15.0f, 0.0f);
		mCrackPos[0] = Vector3(190.0f, 180.0f, -0.5f);
		mCrackPos[1] = Vector3(-110.0f, 245.0f, -0.5f);
		mCrackPos[2] = Vector3(-70.0f, -130.0f, -0.5f);
		mStartPos = Vector3(170.0f, -205.0f, -1.0f);
		mGatePos[0] = Vector3(170.0f, 375.0f, -0.1f);
		mGatePos[1] = Vector3(207.0f, 375.0f, -0.1f);
		mGatePos[2] = Vector3(244.0f, 375.0f, -0.1f);

		mRewardPos = mGatePos[1];
		mRewardPos.y -= 80.0f;

		object::Instantiate<Img_Stage0_Map>(Img_Stage0_Map::Stage0::forestfd03, pos, eLayerType::BGImg, this);
		object::Instantiate<Img_StartingPlate>(mStartPos, eLayerType::BGImg, this);

		GameObject* Forest03camera = object::Instantiate<GameObject>(cameraPos, eLayerType::BGImg, this);
		mCamera = Forest03camera->AddComp<Camera>();
		Forest03camera->AddComp<SCRIPT_MainCamera>();

		Img_Crack* crack0 = object::Instantiate<Img_Crack>(mCrackPos[0], eLayerType::BGImg, this);
		Img_Crack* crack1 = object::Instantiate<Img_Crack>(mCrackPos[1], eLayerType::BGImg, this);
		Img_Crack* crack2 = object::Instantiate<Img_Crack>(mCrackPos[2], eLayerType::BGImg, this);

		object::Instantiate<Img_RewardPlate>(mRewardPos, eLayerType::BGImg, this);

		mGate0 = object::Instantiate<Interact_Gate>(0, mGatePos[0], eLayerType::InteractableObject, this);
		mGate1 = object::Instantiate<Interact_Gate>(0, mGatePos[1], eLayerType::InteractableObject, this);
		mGate2 = object::Instantiate<Interact_Gate>(0, mGatePos[2], eLayerType::InteractableObject, this);

		mGate0->SetNextScene(L"05_Stage0_Forest04");
		mGate1->SetNextScene(L"05_Stage0_Forest04");
		mGate2->SetNextScene(L"05_Stage0_Forest04");

#pragma region Monsters
		//object::Instantiate<Melee_SlimeA>(eLayerType::Monster, this);
		//object::Instantiate<Melee_SlimeA>(eLayerType::Monster, this);
		//object::Instantiate<Melee_SlimeA>(eLayerType::Monster, this);
		//object::Instantiate<Melee_SlimeA>(eLayerType::Monster, this);
		//object::Instantiate<Melee_SlimeA>(eLayerType::Monster, this);
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
		//object::Instantiate<Melee_Cannibals>(eLayerType::Monster, this);
		//object::Instantiate<Melee_Cannibals>(eLayerType::Monster, this);
		//object::Instantiate<Ranged_CannibalFlowerA>(eLayerType::Monster, this);
		//object::Instantiate<Ranged_CannibalFlowerA>(eLayerType::Monster, this);
		//object::Instantiate<Ranged_CannibalFlowerA>(eLayerType::Monster, this);
		//object::Instantiate<Ranged_CannibalFlowerA>(eLayerType::Monster, this);
		//object::Instantiate<Ranged_CannibalFlowerA>(eLayerType::Monster, this);
		//object::Instantiate<Ranged_Ent>(eLayerType::Monster, this);
		//object::Instantiate<Ranged_Ent>(eLayerType::Monster, this);
		//object::Instantiate<Ranged_Ent>(eLayerType::Monster, this);
		//object::Instantiate<Ranged_Ent>(eLayerType::Monster, this);
		//object::Instantiate<Ranged_Ent>(eLayerType::Monster, this);
#pragma endregion

		PlayScene::Initialize();
	}
	void Stage0_Forest03::Update()
	{
		PlayScene::Update();
	}
	void Stage0_Forest03::LateUpdate()
	{
		PlayScene::LateUpdate();
	}
	void Stage0_Forest03::Render()
	{
		PlayScene::Render();
	}
	void Stage0_Forest03::OnEnter()
	{
		renderer::mainCamera = mCamera;

		PlayScene::OnEnter();
		Player->GetComp<Transform>()->SetPosition(mStartPos);

		const std::wstring path0 = { L"..\\Resources\\Tile\\forestfd03_00" };
		TilePalette::AutoLoad(path0);

	}
	void Stage0_Forest03::OnExit()
	{
		PlayScene::OnExit();
		mFocus->DeleteSelectobj(mGate0);
		mFocus->DeleteSelectobj(mGate1);
		mFocus->DeleteSelectobj(mGate2);

	}
}