#include "Stage0_Forest05.h"

#include "Stage0_Forest05.h"
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
	Stage0_Forest05::Stage0_Forest05()
	{
		SetName(L"07_Stage0_Forest05");
	}
	Stage0_Forest05::~Stage0_Forest05()
	{
	}
	void Stage0_Forest05::Initialize()
	{
		Vector3 cameraPos = Vector3(0.0f, 0.0f, -10.0f);
		Vector3 pos = Vector3(0.0f, -3.0f, 0.0f);
		mCrackPos[0] = Vector3(165.0f, -180.0f, -0.5f);
		mCrackPos[1] = Vector3(0.0f, -55.0f, -0.5f);
		mCrackPos[2] = Vector3(-15.0f, 240.0f, -0.5f);
		mStartPos = Vector3(-300.0f, 95.0f, -1.0f);

		object::Instantiate<Img_Stage0_Map>(Img_Stage0_Map::Stage0::forestdg01, pos, eLayerType::BGImg, this);
		object::Instantiate<Img_StartingPlate>(mStartPos, eLayerType::BGImg, this);

		GameObject* Forest05camera = object::Instantiate<GameObject>(cameraPos, eLayerType::BGImg, this);
		mCamera = Forest05camera->AddComp<Camera>();
		Forest05camera->AddComp<SCRIPT_MainCamera>();

		Img_Crack* crack0 = object::Instantiate<Img_Crack>(mCrackPos[0], eLayerType::BGImg, this);
		Img_Crack* crack1 = object::Instantiate<Img_Crack>(mCrackPos[1], eLayerType::BGImg, this);
		Img_Crack* crack2 = object::Instantiate<Img_Crack>(mCrackPos[2], eLayerType::BGImg, this);

		Vector3 gpos0 = Vector3(-82.0f, 390.0f, -0.1f);
		Vector3 gpos1 = Vector3(-45.0f, 390.0f, -0.1f);
		Vector3 gpos2 = Vector3(-8.0, 390.0f, -0.1f);

		mRewardPos = gpos1;
		mRewardPos.y -= 80.0f;
		object::Instantiate<Img_RewardPlate>(mRewardPos, eLayerType::BGImg, this);

		mGate0 = object::Instantiate<Interact_Gate>(0, gpos0, eLayerType::InteractableObject, this);
		mGate1 = object::Instantiate<Interact_Gate>(0, gpos1, eLayerType::InteractableObject, this);
		mGate2 = object::Instantiate<Interact_Gate>(0, gpos2, eLayerType::InteractableObject, this);

		mGate0->SetNextScene(L"02_LobbyScene");
		mGate1->SetNextScene(L"02_LobbyScene");
		mGate2->SetNextScene(L"02_LobbyScene");

		gpos0.y += 20.0;
		gpos1.y += 20.0;
		gpos2.y += 20.0;

		mItem0 = MakeItem(gpos0);
		mItem1 = MakeItem(gpos1);
		mItem2 = MakeItem(gpos2);

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
	void Stage0_Forest05::Update()
	{
		PlayScene2::Update();
	}
	void Stage0_Forest05::LateUpdate()
	{
		PlayScene2::LateUpdate();
	}
	void Stage0_Forest05::Render()
	{
		PlayScene2::Render();
	}
	void Stage0_Forest05::OnEnter()
	{
		renderer::mainCamera = mCamera;

		PlayScene2::OnEnter();

		const std::wstring path0 = { L"..\\Resources\\Tile\\forestdg01_00" };
		TilePalette::AutoLoad(path0);

	}
	void Stage0_Forest05::OnExit()
	{
		PlayScene2::OnExit();
		mFocus->DeleteSelectobj(mGate0);
		mFocus->DeleteSelectobj(mGate1);
		mFocus->DeleteSelectobj(mGate2);

	}
}