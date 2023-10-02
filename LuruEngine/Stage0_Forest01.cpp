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

		object::Instantiate<Img_Stage0_Map>(Img_Stage0_Map::Stage0::forestfd01, pos, eLayerType::BGImg, this);
		object::Instantiate<Img_StartingPlate>(mStartPos, eLayerType::BGImg, this);
		GameObject* Forest01camera = object::Instantiate<GameObject>(cameraPos, eLayerType::BGImg, this);
		mCamera = Forest01camera->AddComp<Camera>();
		Forest01camera->AddComp<SCRIPT_MainCamera>();

		Img_Crack* crack0 = object::Instantiate<Img_Crack>(mCrackPos[0], eLayerType::BGImg, this);
		Img_Crack* crack1 = object::Instantiate<Img_Crack>(mCrackPos[1], eLayerType::BGImg, this);
		Img_Crack* crack2 = object::Instantiate<Img_Crack>(mCrackPos[2], eLayerType::BGImg, this);

		Vector3 gpos0 = Vector3(-210.0f, 380.0f, -0.1f);
		Vector3 gpos1 = Vector3(-173.0f, 380.0f, -0.1f);
		Vector3 gpos2 = Vector3(-136.0f, 380.0f, -0.1f);

		mRewardPos = gpos1;
		mRewardPos.y -= 80.0f;
		object::Instantiate<Img_RewardPlate>(mRewardPos, eLayerType::BGImg, this);

		mGate0 = object::Instantiate<Interact_Gate>(0, gpos0, eLayerType::InteractableObject, this);
		mGate1 = object::Instantiate<Interact_Gate>(0, gpos1, eLayerType::InteractableObject, this);
		mGate2 = object::Instantiate<Interact_Gate>(0, gpos2, eLayerType::InteractableObject, this);

		mGate0->SetNextScene(L"04_Stage0_Forest02");
		mGate1->SetNextScene(L"04_Stage0_Forest02");
		mGate2->SetNextScene(L"04_Stage0_Forest02");

		gpos0.y += 30.0f;
		gpos1.y += 30.0f;
		gpos2.y += 30.0f;

		mItem0 = MakeItem(gpos0);
		mItem1 = MakeItem(gpos1);
		mItem2 = MakeItem(gpos2);



#pragma region Monsters
		//object::Instantiate<Boss_SkelKnight>(eLayerType::Monster, this);
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