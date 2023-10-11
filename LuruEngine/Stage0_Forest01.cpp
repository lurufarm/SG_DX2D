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
#include "Img_StartingPlate.h"
#include "Img_RewardPlate.h"
#include "Gobj_Player.h"
#include "Monsters.h"
#include "UI_FocusBoxes2.h"
#include "Interact_Gate.h"
#include "Item_AbilityEnhancer.h"
#include "Item_Selected.h"

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
		mCrackPos[0] = Vector3(90.0f, 130.0f, -0.5f);
		mCrackPos[1] = Vector3(-140.0f, 265.0f, -0.5f);
		mCrackPos[2] = Vector3(-315.0f, 155.0f, -0.5f);
		mStartPos = Vector3(-180.0f, -75.0f, -1.0f);
		mGatePos[0] = Vector3(-210.0f, 400.0f, -0.1f);
		mGatePos[1] = Vector3(-173.0f, 400.0f, -0.1f);
		mGatePos[2] = Vector3(-136.0f, 400.0f, -0.1f);

		mRewardPos = mGatePos[1];
		mRewardPos.y -= 80.0f;

		object::Instantiate<Img_Stage0_Map>(Img_Stage0_Map::Stage0::forestfd01, pos, eLayerType::BGImg, this);
		object::Instantiate<Img_StartingPlate>(mStartPos, eLayerType::BGImg, this);
		GameObject* Forest01camera = object::Instantiate<GameObject>(cameraPos, eLayerType::BGImg, this);
		mCamera = Forest01camera->AddComp<Camera>();
		Forest01camera->AddComp<SCRIPT_MainCamera>();

		Img_Crack* crack0 = object::Instantiate<Img_Crack>(mCrackPos[0], eLayerType::BGImg, this);
		Img_Crack* crack1 = object::Instantiate<Img_Crack>(mCrackPos[1], eLayerType::BGImg, this);
		Img_Crack* crack2 = object::Instantiate<Img_Crack>(mCrackPos[2], eLayerType::BGImg, this);

		object::Instantiate<Img_RewardPlate>(mRewardPos, eLayerType::BGImg, this);

		mGate0 = object::Instantiate<Interact_Gate>(0, mGatePos[0], eLayerType::InteractableObject, this);
		mGate1 = object::Instantiate<Interact_Gate>(0, mGatePos[1], eLayerType::InteractableObject, this);
		mGate2 = object::Instantiate<Interact_Gate>(0, mGatePos[2], eLayerType::InteractableObject, this);

		mGate0->SetNextScene(L"04_Stage0_Forest02");
		mGate1->SetNextScene(L"04_Stage0_Forest02");
		mGate2->SetNextScene(L"04_Stage0_Forest02");

#pragma region Monsters
		object::Instantiate<Ranged_FireLizard>(eLayerType::Monster, this);



		//object::Instantiate<Melee_SlimeA>(eLayerType::Monster, this);
		//object::Instantiate<Melee_SlimeA>(eLayerType::Monster, this);
		//object::Instantiate<Melee_SlimeA>(eLayerType::Monster, this);
		//object::Instantiate<Melee_SlimeA>(eLayerType::Monster, this);
		//object::Instantiate<Melee_SlimeA>(eLayerType::Monster, this);
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
#pragma endregion

		PlayScene::Initialize();

	}
	void Stage0_Forest01::Update()
	{
		std::wstring charName = Player->GetChar()->GetName();
		if (charName == L"Cheese")
			SelectedItemID = 20;
		else if (charName == L"Lucy")
			SelectedItemID = 21;
		else if (charName == L"Robo")
			SelectedItemID = 22;

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

		const std::wstring path0 = { L"..\\Resources\\Tile\\forestfd01_01" };
		TilePalette::AutoLoad(path0);

	}
	void Stage0_Forest01::OnExit()
	{
		mFocus->DeleteSelectobj(mGate0);
		mFocus->DeleteSelectobj(mGate1);
		mFocus->DeleteSelectobj(mGate2);
		PlayScene::OnExit();
	}
}