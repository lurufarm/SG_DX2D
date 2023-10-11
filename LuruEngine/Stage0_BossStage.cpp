#include "Stage0_BossStage.h"

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
	Stage0_BossStage::Stage0_BossStage()
	{
		SetName(L"11_Stage0_BossStage");
	}
	Stage0_BossStage::~Stage0_BossStage()
	{
	}
	void Stage0_BossStage::Initialize()
	{
		Vector3 cameraPos = Vector3(0.0f, 0.0f, -10.0f);
		Vector3 pos = Vector3(-4.0f, -3.0f, 0.0f);
		mStartPos = Vector3(-95.0f, -190.0f, -1.0f);
		mCrackPos[0] = Vector3(145.0f, 150.0f, -0.5f);
		mCrackPos[1] = Vector3(-175.0f, 30.0f, -0.5f);
		mCrackPos[2] = Vector3(10.0f, -10, -0.5f);
		mGatePos[0] = Vector3(-63.0f, 265.0f, -0.1f);
		mGatePos[1] = Vector3(-33.0f, 265.0f, -0.1f);
		mGatePos[2] = Vector3(-3.0, 265.0f, -0.1f);
		mRewardPos = mGatePos[1];
		mRewardPos.y -= 80.0f;

		object::Instantiate<Img_Stage0_Map>(Img_Stage0_Map::Stage0::forestboss01, pos, eLayerType::BGImg, this);
		object::Instantiate<Img_StartingPlate>(mStartPos, eLayerType::BGImg, this);

		GameObject* Forest08camera = object::Instantiate<GameObject>(cameraPos, eLayerType::BGImg, this);
		mCamera = Forest08camera->AddComp<Camera>();
		Forest08camera->AddComp<SCRIPT_MainCamera>();

		object::Instantiate<Img_Torch>(Vector3(150, -170, -0.1f), eLayerType::BGImg, this);
		object::Instantiate<Img_Torch>(Vector3(-135, -75, -0.1f), eLayerType::BGImg, this);
		object::Instantiate<Img_Torch>(Vector3(-100, 100, -0.1f), eLayerType::BGImg, this);
		object::Instantiate<Img_Torch>(Vector3(90, 205, -0.1f), eLayerType::BGImg, this);
		object::Instantiate<Img_Torch>(Vector3(-45, -10, -0.1f), eLayerType::BGImg, this);

		mCrack0 = object::Instantiate<Img_Crack>(mCrackPos[0], eLayerType::BGImg, this);
		mCrack1 = object::Instantiate<Img_Crack>(mCrackPos[1], eLayerType::BGImg, this);
		mCrack2 = object::Instantiate<Img_Crack>(mCrackPos[2], eLayerType::BGImg, this);

		object::Instantiate<Img_RewardPlate>(mRewardPos, eLayerType::BGImg, this);

		mGate0 = object::Instantiate<Interact_Gate>(0, mGatePos[0], eLayerType::InteractableObject, this);
		mGate1 = object::Instantiate<Interact_Gate>(0, mGatePos[1], eLayerType::InteractableObject, this);
		mGate2 = object::Instantiate<Interact_Gate>(0, mGatePos[2], eLayerType::InteractableObject, this);

		mGate0->SetNextScene(L"20_Stage1_Desert01");
		mGate1->SetNextScene(L"20_Stage1_Desert01");
		mGate2->SetNextScene(L"20_Stage1_Desert01");

#pragma region Monsters
		//object::Instantiate<Melee_SlimeB>(eLayerType::Monster, this);

#pragma endregion

		PlayScene2::Initialize();
	}
	void Stage0_BossStage::Update()
	{
		PlayScene2::Update();
	}
	void Stage0_BossStage::LateUpdate()
	{
		PlayScene2::LateUpdate();
	}
	void Stage0_BossStage::Render()
	{
		PlayScene2::Render();
	}
	void Stage0_BossStage::OnEnter()
	{
		renderer::mainCamera = mCamera;

		PlayScene2::OnEnter();

		const std::wstring path0 = { L"..\\Resources\\Tile\\forestboss" };
		TilePalette::AutoLoad(path0);
	}
	void Stage0_BossStage::OnExit()
	{
		PlayScene2::OnExit();
		mFocus->DeleteSelectobj(mGate0);
		mFocus->DeleteSelectobj(mGate1);
		mFocus->DeleteSelectobj(mGate2);

	}
}