#include "Stage1_MidBoss.h"
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
#include "UI_StatusBase.h"
#include "Img_Finish.h"
#include "Gobj_Sound.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	Stage1_MidBoss::Stage1_MidBoss()
	{
		SetName(L"24_Stage1_MidBoss");
	}
	Stage1_MidBoss::~Stage1_MidBoss()
	{
	}
	void Stage1_MidBoss::Initialize()
	{
		mBGM = object::Instantiate<Gobj_Sound>(eLayerType::BG, this);
		mBGM->SetSound(L"BGM_BOSS");
		mBGM->SetSoundLoop(true);

		Vector3 cameraPos = Vector3(0.0f, 0.0f, -10.0f);
		Vector3 pos = Vector3(-4.5f, -3.0f, 0.0f);
		mCrackPos[0] = Vector3(-200.0f, 40.0f, -0.5f);
		mCrackPos[1] = Vector3(-50.0f, 180.0f, -0.5f);
		mCrackPos[2] = Vector3(35.0f, -5.0f, -0.5f);
		mStartPos = Vector3(-115.0f, -170.0f, -1.0f);
		mGatePos[0] = Vector3(-80.0f, 355.0f, -0.1f);
		mGatePos[1] = Vector3(-50.0f, 355.0f, -0.1f);
		mGatePos[2] = Vector3(-20.0f, 355.0f, -0.1f);

		mRewardPos = mGatePos[1];
		mRewardPos.y -= 80.0f;

		object::Instantiate<Img_Stage1_Map>(Img_Stage1_Map::Stage1::desertmidboss, pos, eLayerType::BG, this);
		object::Instantiate<Img_StartingPlate>(mStartPos, eLayerType::BG, this);

		GameObject* DesertMidBosscamera = object::Instantiate<GameObject>(cameraPos, eLayerType::BG, this);
		mCamera = DesertMidBosscamera->AddComp<Camera>();
		DesertMidBosscamera->AddComp<SCRIPT_MainCamera>();

		object::Instantiate<Img_Torch>(Vector3(-155, -60, -0.1f), eLayerType::BG, this);
		object::Instantiate<Img_Torch>(Vector3(-125, 120, -0.1f), eLayerType::BG, this);
		object::Instantiate<Img_Torch>(Vector3(40, 245, -0.1f), eLayerType::BG, this);
		object::Instantiate<Img_Torch>(Vector3(135, 35, -0.1f), eLayerType::BG, this);

		mCrack0 = object::Instantiate<Img_Crack>(mCrackPos[0], eLayerType::BG, this);
		mCrack1 = object::Instantiate<Img_Crack>(mCrackPos[1], eLayerType::BG, this);
		mCrack2 = object::Instantiate<Img_Crack>(mCrackPos[2], eLayerType::BG, this);

		mGate0 = object::Instantiate<Interact_Gate>(0, mGatePos[0], eLayerType::InteractableObject, this);
		mGate1 = object::Instantiate<Interact_Gate>(0, mGatePos[1], eLayerType::InteractableObject, this);
		mGate2 = object::Instantiate<Interact_Gate>(0, mGatePos[2], eLayerType::InteractableObject, this);


#pragma region Monsters
		//object::Instantiate<Boss_Centipede>(eLayerType::Monster, this);
#pragma endregion

		PlayScene2::Initialize();
	}
	void Stage1_MidBoss::Update()
	{
		if (Input::KeyD(eKeyCode::J))
		{
			if (mStatus->GetState() == GameObject::eState::Paused)
			{
				mStatus->SetState(GameObject::eState::Active);
				mStatus->StateUpdate();
			}
			else if (mStatus->GetState() == GameObject::eState::Active)
			{
				mStatus->SetState(GameObject::eState::Paused);
				mStatus->StateUpdate();
			}
		}

		if (mActiveMobs.size() == 0 && mPausedMobs.size() == 0 && mClear == false)
		{
			object::Instantiate<Img_Finish>(eLayerType::UI_Box, this);
			mClear = true;
		}
		if (mActiveMobs.size() < 5)
			SpawnMob();
		PurgeDeadMobs();

		Scene::Update();
	}
	void Stage1_MidBoss::LateUpdate()
	{
		PlayScene2::LateUpdate();
	}
	void Stage1_MidBoss::Render()
	{
		PlayScene2::Render();
	}
	void Stage1_MidBoss::OnEnter()
	{
		renderer::mainCamera = mCamera;

		PlayScene2::OnEnter();

		const std::wstring path0 = { L"..\\Resources\\Tile\\desertmidboss" };
		TilePalette::AutoLoad(path0);
		mBGM->Play();
	}
	void Stage1_MidBoss::OnExit()
	{
		mBGM->Stop();

		PlayScene2::OnExit();
		mFocus->DeleteSelectobj(mGate0);
		mFocus->DeleteSelectobj(mGate1);
		mFocus->DeleteSelectobj(mGate2);

	}
}