#include "Stage1_Desert01.h"
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
#include "UI_FocusBoxes2.h"
#include "Interact_Gate.h"
#include "Item_AbilityEnhancer.h"
#include "Item_Selected.h"
#include "Gobj_Sound.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	Stage1_Desert01::Stage1_Desert01()
	{
		SetName(L"20_Stage1_Desert01");
	}
	Stage1_Desert01::~Stage1_Desert01()
	{
	}
	void Stage1_Desert01::Initialize()
	{
		mBGM = object::Instantiate<Gobj_Sound>(eLayerType::BG, this);
		mBGM->SetSound(L"BGM_DFD");
		mBGM->SetSoundLoop(true);

		Vector3 cameraPos = Vector3(0.0f, 0.0f, -10.0f);
		Vector3 pos = Vector3(-4.5f, -3.0f, 0.0f);
		mCrackPos[0] = Vector3(95.0f, 0.0f, -0.5f);
		mCrackPos[1] = Vector3(-105.0f, 170.0f, -0.5f);
		mCrackPos[2] = Vector3(-85.0f, -45.0f, -0.5f);
		mStartPos = Vector3(-25.0f, -185.0f, -1.0f);
		mGatePos[0] = Vector3(-70.0f, 255.0f, -0.1f);
		mGatePos[1] = Vector3(-40.0f, 255.0f, -0.1f);
		mGatePos[2] = Vector3(-10.0f, 255.0f, -0.1f);

		mRewardPos = mGatePos[1];
		mRewardPos.y -= 80.0f;
		object::Instantiate<Img_Stage1_Map>(Img_Stage1_Map::Stage1::desert01, pos, eLayerType::BG, this);
		object::Instantiate<Img_StartingPlate>(mStartPos, eLayerType::BG, this);
		GameObject* Desert01camera = object::Instantiate<GameObject>(cameraPos, eLayerType::BG, this);
		mCamera = Desert01camera->AddComp<Camera>();
		Desert01camera->AddComp<SCRIPT_MainCamera>();


		object::Instantiate<Img_Torch>(Vector3(-185, -100, -0.1f), eLayerType::BG, this);
		object::Instantiate<Img_Torch>(Vector3(70, -150, -0.1f), eLayerType::BG, this);
		object::Instantiate<Img_Torch>(Vector3(170, 25, -0.1f), eLayerType::BG, this);
		object::Instantiate<Img_Torch>(Vector3(45, 205, -0.1f), eLayerType::BG, this);
		object::Instantiate<Img_Torch>(Vector3(-125, 155, -0.1f), eLayerType::BG, this);

		Img_Crack* crack0 = object::Instantiate<Img_Crack>(mCrackPos[0], eLayerType::BG, this);
		Img_Crack* crack1 = object::Instantiate<Img_Crack>(mCrackPos[1], eLayerType::BG, this);
		Img_Crack* crack2 = object::Instantiate<Img_Crack>(mCrackPos[2], eLayerType::BG, this);

		object::Instantiate<Img_RewardPlate>(mRewardPos, eLayerType::BG, this);

		mGate0 = object::Instantiate<Interact_Gate>(0, mGatePos[0], eLayerType::InteractableObject, this);
		mGate1 = object::Instantiate<Interact_Gate>(0, mGatePos[1], eLayerType::InteractableObject, this);
		mGate2 = object::Instantiate<Interact_Gate>(0, mGatePos[2], eLayerType::InteractableObject, this);

		mGate0->SetNextScene(L"21_Stage1_Desert02");
		mGate1->SetNextScene(L"21_Stage1_Desert02");
		mGate2->SetNextScene(L"21_Stage1_Desert02");

#pragma region Monsters

		//object::Instantiate<Melee_Bee>(eLayerType::Monster, this);
		//object::Instantiate<Melee_Bee>(eLayerType::Monster, this);
		//object::Instantiate<Melee_Bee>(eLayerType::Monster, this);
		//object::Instantiate<Melee_Bee>(eLayerType::Monster, this);
		//object::Instantiate<Melee_Bee>(eLayerType::Monster, this);
		//object::Instantiate<Melee_Bee>(eLayerType::Monster, this);
		//object::Instantiate<Melee_Bee>(eLayerType::Monster, this);
		//object::Instantiate<Melee_EliteBee>(eLayerType::Monster, this);
		//object::Instantiate<Melee_EliteBee>(eLayerType::Monster, this);
		//object::Instantiate<Melee_EliteBee>(eLayerType::Monster, this);
		//object::Instantiate<Melee_Snake>(eLayerType::Monster, this);
		//object::Instantiate<Melee_Snake>(eLayerType::Monster, this);
		//object::Instantiate<Melee_Snake>(eLayerType::Monster, this);
		//object::Instantiate<Melee_Snake>(eLayerType::Monster, this);
		//object::Instantiate<Melee_Snake>(eLayerType::Monster, this);
		//object::Instantiate<Melee_LizardSword>(eLayerType::Monster, this);
		//object::Instantiate<Melee_LizardSword>(eLayerType::Monster, this);
		//object::Instantiate<Melee_LizardSword>(eLayerType::Monster, this);
		//object::Instantiate<Melee_LizardSword>(eLayerType::Monster, this);
		//object::Instantiate<Melee_LizardSword>(eLayerType::Monster, this);
		//object::Instantiate<Ranged_WormEggs>(eLayerType::Monster, this);
		//object::Instantiate<Ranged_WormEggs>(eLayerType::Monster, this);
		//object::Instantiate<Ranged_WormEggs>(eLayerType::Monster, this);
		//object::Instantiate<Ranged_WormEggs>(eLayerType::Monster, this);
		//object::Instantiate<Ranged_WormEggs>(eLayerType::Monster, this);
#pragma endregion

		PlayScene::Initialize();

	}
	void Stage1_Desert01::Update()
	{
		PlayScene::Update();
	}
	void Stage1_Desert01::LateUpdate()
	{
		PlayScene::LateUpdate();
	}
	void Stage1_Desert01::Render()
	{
		PlayScene::Render();
	}
	void Stage1_Desert01::OnEnter()
	{
		renderer::mainCamera = mCamera;
		PlayScene::OnEnter();
		
		const std::wstring path0 = { L"..\\Resources\\Tile\\desert01" };
		TilePalette::AutoLoad(path0);

		mBGM->Play();

	}
	void Stage1_Desert01::OnExit()
	{
		mBGM->Stop();

		mFocus->DeleteSelectobj(mGate0);
		mFocus->DeleteSelectobj(mGate1);
		mFocus->DeleteSelectobj(mGate2);
		PlayScene::OnExit();
	}
}