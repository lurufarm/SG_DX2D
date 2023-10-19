#include "Stage1_Desert03.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgRenderer.h"
#include "..\Engine_SOURCE\sgCollisionManager.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgCamera.h"

#include "Tile_TilePalette.h"
#include "SCRIPT_MainCamera.h"
#include "Img_Stage0_Forest01_Map.h"
#include "Img_Stage1_Desert_Map.h"
#include "Img_Crack.h"
#include "Img_Torch.h"
#include "Img_StartingPlate.h"
#include "Img_RewardPlate.h"
#include "Gobj_Player.h"
#include "Monsters.h"
#include "Interact_Gate.h"
#include "UI_FocusBoxes2.h"
#include "Img_Torch.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	Stage1_Desert03::Stage1_Desert03()
	{
		SetName(L"22_Stage1_Desert03");
	}
	Stage1_Desert03::~Stage1_Desert03()
	{
	}
	void Stage1_Desert03::Initialize()
	{
		Vector3 cameraPos = Vector3(0.0f, 0.0f, -10.0f);
		Vector3 pos = Vector3(0.0f, -3.0f, 0.0f);
		mCrackPos[0] = Vector3(-145.0f, -105.0f, -0.5f);
		mCrackPos[1] = Vector3(90.0f, 175.0f, -0.5f);
		mCrackPos[2] = Vector3(-150.0f, 130.0f, -0.5f);
		mStartPos = Vector3(230.0f, -100.0f, -1.0f);
		mGatePos[0] = Vector3(-95.0f, 285.0f, -0.1f);
		mGatePos[1] = Vector3(-65.0f, 285.0f, -0.1f);
		mGatePos[2] = Vector3(-35.0f, 285.0f, -0.1f);

		mRewardPos = mGatePos[1];
		mRewardPos.y -= 80.0f;

		object::Instantiate<Img_Stage1_Map>(Img_Stage1_Map::Stage1::desert03, pos, eLayerType::BGImg, this);
		object::Instantiate<Img_StartingPlate>(mStartPos, eLayerType::BGImg, this);

		GameObject* Desert03camera = object::Instantiate<GameObject>(cameraPos, eLayerType::BGImg, this);
		mCamera = Desert03camera->AddComp<Camera>();
		Desert03camera->AddComp<SCRIPT_MainCamera>();

		object::Instantiate<Img_Torch>(Vector3(205, -25, -0.1f), eLayerType::BGImg, this);
		object::Instantiate<Img_Torch>(Vector3(-240, -50, -0.1f), eLayerType::BGImg, this);
		object::Instantiate<Img_Torch>(Vector3(-255, 0, -0.1f), eLayerType::BGImg, this);
		object::Instantiate<Img_Torch>(Vector3(-10, 100, -0.1f), eLayerType::BGImg, this);
		object::Instantiate<Img_Torch>(Vector3(-135, 215, -0.1f), eLayerType::BGImg, this);

		mCrack0 = object::Instantiate<Img_Crack>(mCrackPos[0], eLayerType::BGImg, this);
		mCrack1 = object::Instantiate<Img_Crack>(mCrackPos[1], eLayerType::BGImg, this);
		mCrack2 = object::Instantiate<Img_Crack>(mCrackPos[2], eLayerType::BGImg, this);

		object::Instantiate<Img_RewardPlate>(mRewardPos, eLayerType::BGImg, this);

		mGate0 = object::Instantiate<Interact_Gate>(0, mGatePos[0], eLayerType::InteractableObject, this);
		mGate1 = object::Instantiate<Interact_Gate>(0, mGatePos[1], eLayerType::InteractableObject, this);
		mGate2 = object::Instantiate<Interact_Gate>(0, mGatePos[2], eLayerType::InteractableObject, this);

		mGate0->SetNextScene(L"23_Stage1_Desert04");
		mGate1->SetNextScene(L"23_Stage1_Desert04");
		mGate2->SetNextScene(L"23_Stage1_Desert04");

#pragma region Monsters
		object::Instantiate<Melee_Mummy>(eLayerType::Monster, this);
		object::Instantiate<Melee_Mummy>(eLayerType::Monster, this);
		object::Instantiate<Melee_Mummy>(eLayerType::Monster, this);
		object::Instantiate<Melee_Mummy>(eLayerType::Monster, this);
		object::Instantiate<Melee_Mummy>(eLayerType::Monster, this);
		object::Instantiate<Melee_Snake>(eLayerType::Monster, this);
		object::Instantiate<Melee_Snake>(eLayerType::Monster, this);
		object::Instantiate<Melee_Snake>(eLayerType::Monster, this);
		object::Instantiate<Melee_MummyPoison>(eLayerType::Monster, this);
		object::Instantiate<Melee_MummyPoison>(eLayerType::Monster, this);
		object::Instantiate<Melee_MummyPoison>(eLayerType::Monster, this);
		object::Instantiate<Melee_MummyPoison>(eLayerType::Monster, this);
		object::Instantiate<Ranged_MummyBomb>(eLayerType::Monster, this);
		object::Instantiate<Ranged_MummyBomb>(eLayerType::Monster, this);
		object::Instantiate<Ranged_MummyBomb>(eLayerType::Monster, this);
		object::Instantiate<Ranged_MummyBomb>(eLayerType::Monster, this);
		object::Instantiate<Melee_LizardSword>(eLayerType::Monster, this);
		object::Instantiate<Melee_LizardSword>(eLayerType::Monster, this);
		object::Instantiate<Melee_LizardSword>(eLayerType::Monster, this);
		object::Instantiate<Ranged_LizardSpear>(eLayerType::Monster, this);
		object::Instantiate<Ranged_LizardSpear>(eLayerType::Monster, this);
		object::Instantiate<Ranged_LizardSpear>(eLayerType::Monster, this);
		object::Instantiate<Ranged_FireLizard>(eLayerType::Monster, this);
		object::Instantiate<Ranged_FireLizard>(eLayerType::Monster, this);
		object::Instantiate<Ranged_FireLizard>(eLayerType::Monster, this);
		object::Instantiate<Ranged_Janubis>(eLayerType::Monster, this);
		object::Instantiate<Ranged_Janubis>(eLayerType::Monster, this);
		object::Instantiate<Ranged_Janubis>(eLayerType::Monster, this);

#pragma endregion

		PlayScene2::Initialize();
	}
	void Stage1_Desert03::Update()
	{
		PlayScene2::Update();
	}
	void Stage1_Desert03::LateUpdate()
	{
		PlayScene2::LateUpdate();
	}
	void Stage1_Desert03::Render()
	{
		PlayScene2::Render();
	}
	void Stage1_Desert03::OnEnter()
	{
		renderer::mainCamera = mCamera;

		PlayScene2::OnEnter();

		const std::wstring path0 = { L"..\\Resources\\Tile\\desert03" };
		TilePalette::AutoLoad(path0);

	}
	void Stage1_Desert03::OnExit()
	{
		PlayScene2::OnExit();
		mFocus->DeleteSelectobj(mGate0);
		mFocus->DeleteSelectobj(mGate1);
		mFocus->DeleteSelectobj(mGate2);

	}
}