#include "Stage1_Desert04.h"
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
#include "Gobj_Sound.h"
#include "Stage1_Desert03.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	Stage1_Desert04::Stage1_Desert04()
	{
		SetName(L"23_Stage1_Desert04");
	}
	Stage1_Desert04::~Stage1_Desert04()
	{
	}
	void Stage1_Desert04::Initialize()
	{
		Vector3 cameraPos = Vector3(0.0f, 0.0f, -10.0f);
		Vector3 pos = Vector3(-4.5f, -3.0f, 0.0f);
		mCrackPos[0] = Vector3(95.0f, -125.0f, -0.5f);
		mCrackPos[1] = Vector3(-180.0f, 105.0f, -0.5f);
		mCrackPos[2] = Vector3(220.0f, 5.0f, -0.5f);
		mStartPos = Vector3(-190.0f, -190.0f, -1.0f);
		mGatePos[0] = Vector3(7.0f, 268.0f, -0.1f);
		mGatePos[1] = Vector3(37.0f, 268.0f, -0.1f);
		mGatePos[2] = Vector3(67.0f, 268.0f, -0.1f);

		mRewardPos = mGatePos[1];
		mRewardPos.y -= 80.0f;

		object::Instantiate<Img_Stage1_Map>(Img_Stage1_Map::Stage1::desert04, pos, eLayerType::BG, this);
		object::Instantiate<Img_StartingPlate>(mStartPos, eLayerType::BG, this);

		GameObject* Desert04camera = object::Instantiate<GameObject>(cameraPos, eLayerType::BG, this);
		mCamera = Desert04camera->AddComp<Camera>();
		Desert04camera->AddComp<SCRIPT_MainCamera>();

		object::Instantiate<Img_Torch>(Vector3(-190, -100, -0.1f), eLayerType::BG, this);
		object::Instantiate<Img_Torch>(Vector3(-250, 170, -0.1f), eLayerType::BG, this);
		object::Instantiate<Img_Torch>(Vector3(140, 215, -0.1f), eLayerType::BG, this);
		object::Instantiate<Img_Torch>(Vector3(200, -75, -0.1f), eLayerType::BG, this);

		mCrack0 = object::Instantiate<Img_Crack>(mCrackPos[0], eLayerType::BG, this);
		mCrack1 = object::Instantiate<Img_Crack>(mCrackPos[1], eLayerType::BG, this);
		mCrack2 = object::Instantiate<Img_Crack>(mCrackPos[2], eLayerType::BG, this);

		object::Instantiate<Img_RewardPlate>(mRewardPos, eLayerType::BG, this);

		mGate0 = object::Instantiate<Interact_Gate>(1, mGatePos[0], eLayerType::InteractableObject, this);
		mGate1 = object::Instantiate<Interact_Gate>(1, mGatePos[1], eLayerType::InteractableObject, this);
		mGate2 = object::Instantiate<Interact_Gate>(1, mGatePos[2], eLayerType::InteractableObject, this);

		mGate0->SetNextScene(L"24_Stage1_MidBoss");
		mGate1->SetNextScene(L"24_Stage1_MidBoss");
		mGate2->SetNextScene(L"24_Stage1_MidBoss");

#pragma region Monsters
		object::Instantiate<Ranged_WormEggs>(eLayerType::Monster, this);
		object::Instantiate<Ranged_WormEggs>(eLayerType::Monster, this);
		object::Instantiate<Ranged_WormEggs>(eLayerType::Monster, this);
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
	void Stage1_Desert04::Update()
	{
		PlayScene2::Update();
	}
	void Stage1_Desert04::LateUpdate()
	{
		PlayScene2::LateUpdate();
	}
	void Stage1_Desert04::Render()
	{
		PlayScene2::Render();
	}
	void Stage1_Desert04::OnEnter()
	{
		renderer::mainCamera = mCamera;

		PlayScene2::OnEnter();

		const std::wstring path0 = { L"..\\Resources\\Tile\\desert04" };
		TilePalette::AutoLoad(path0);

	}
	void Stage1_Desert04::OnExit()
	{
		//Gobj_Sound* bgm = dynamic_cast<Stage1_Desert03*>(SceneManager::FindScene(L"22_Stage1_Desert03"))->GetDesertDGBGM();
		//bgm->Stop();

		PlayScene2::OnExit();
		mFocus->DeleteSelectobj(mGate0);
		mFocus->DeleteSelectobj(mGate1);
		mFocus->DeleteSelectobj(mGate2);

	}
}