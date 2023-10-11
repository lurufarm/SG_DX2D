#include "Stage1_Desert02.h"

#include "Stage0_Forest02.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgRenderer.h"
#include "..\Engine_SOURCE\sgCollisionManager.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgCamera.h"

#include "Tile_TilePalette.h"
#include "SCRIPT_MainCamera.h"
#include "Img_Stage1_Desert_Map.h"
#include "Img_Crack.h"
#include "Img_Torch.h"
#include "Img_StartingPlate.h"
#include "Img_RewardPlate.h"
#include "Gobj_Player.h"
#include "Monsters.h"
#include "Interact_Gate.h"
#include "UI_FocusBoxes2.h"
#include "Item_AbilityEnhancer.h"


extern sg::Gobj_Player* Player;

namespace sg
{
	Stage1_Desert02::Stage1_Desert02()
	{
		SetName(L"21_Stage1_Desert02");
	}
	Stage1_Desert02::~Stage1_Desert02()
	{
	}
	void Stage1_Desert02::Initialize()
	{
		Vector3 cameraPos = Vector3(0.0f, 0.0f, -10.0f);
		Vector3 pos = Vector3(65.0f, -75.0f, 0.0f);
		mCrackPos[0] = Vector3(-140.0f, -100.0f, -0.5f);
		mCrackPos[1] = Vector3(90.0f, 35, -0.5f);
		mCrackPos[2] = Vector3(-115.0f, 40.0f, -0.5f);
		mStartPos = Vector3(-190.0f, -240.0f, -1.0f);
		mGatePos[0] = Vector3(-215.0f, 235.0f, -0.1f);
		mGatePos[1] = Vector3(-185.0f, 235.0f, -0.1f);
		mGatePos[2] = Vector3(-155.0f, 235.0f, -0.1f);

		mRewardPos = mGatePos[1];
		mRewardPos.y -= 80.0f;

		object::Instantiate<Img_Stage1_Map>(Img_Stage1_Map::Stage1::desert02, pos, eLayerType::BGImg, this);
		object::Instantiate<Img_StartingPlate>(mStartPos, eLayerType::BGImg, this);

		GameObject* Desert02camera = object::Instantiate<GameObject>(cameraPos, eLayerType::BGImg, this);
		mCamera = Desert02camera->AddComp<Camera>();
		Desert02camera->AddComp<SCRIPT_MainCamera>();

		object::Instantiate<Img_Torch>(Vector3(-85, -185, -0.1f), eLayerType::BGImg, this);
		object::Instantiate<Img_Torch>(Vector3(-210, 0, -0.1f), eLayerType::BGImg, this);
		object::Instantiate<Img_Torch>(Vector3(-105, 180, -0.1f), eLayerType::BGImg, this);
		object::Instantiate<Img_Torch>(Vector3(55, 165, -0.1f), eLayerType::BGImg, this);
		object::Instantiate<Img_Torch>(Vector3(60, -75, -0.1f), eLayerType::BGImg, this);



		Img_Crack* crack0 = object::Instantiate<Img_Crack>(mCrackPos[0], eLayerType::BGImg, this);
		Img_Crack* crack1 = object::Instantiate<Img_Crack>(mCrackPos[1], eLayerType::BGImg, this);
		Img_Crack* crack2 = object::Instantiate<Img_Crack>(mCrackPos[2], eLayerType::BGImg, this);

		object::Instantiate<Img_RewardPlate>(mRewardPos, eLayerType::BGImg, this);

		mGate0 = object::Instantiate<Interact_Gate>(0, mGatePos[0], eLayerType::InteractableObject, this);
		mGate1 = object::Instantiate<Interact_Gate>(0, mGatePos[1], eLayerType::InteractableObject, this);
		mGate2 = object::Instantiate<Interact_Gate>(0, mGatePos[2], eLayerType::InteractableObject, this);

		mGate0->SetNextScene(L"22_Stage1_Desert03");
		mGate1->SetNextScene(L"22_Stage1_Desert03");
		mGate2->SetNextScene(L"22_Stage1_Desert03");

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
#pragma endregion

		PlayScene::Initialize();
	}
	void Stage1_Desert02::Update()
	{
		PlayScene::Update();
	}
	void Stage1_Desert02::LateUpdate()
	{
		PlayScene::LateUpdate();
	}
	void Stage1_Desert02::Render()
	{
		PlayScene::Render();
	}
	void Stage1_Desert02::OnEnter()
	{
		renderer::mainCamera = mCamera;

		PlayScene::OnEnter();

		const std::wstring path0 = { L"..\\Resources\\Tile\\desert02" };
		TilePalette::AutoLoad(path0);

	}
	void Stage1_Desert02::OnExit()
	{
		mFocus->DeleteSelectobj(mGate0);
		mFocus->DeleteSelectobj(mGate1);
		mFocus->DeleteSelectobj(mGate2);
		PlayScene::OnExit();
	}
}