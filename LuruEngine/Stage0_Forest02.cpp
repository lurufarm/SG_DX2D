#include "Stage0_Forest02.h"
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
#include "Item_AbilityEnhancer.h"


extern sg::Gobj_Player* Player;

namespace sg
{
	Stage0_Forest02::Stage0_Forest02()
	{
		SetName(L"04_Stage0_Forest02");
	}
	Stage0_Forest02::~Stage0_Forest02()
	{
	}
	void Stage0_Forest02::Initialize()
	{
		Vector3 cameraPos = Vector3(0.0f, 0.0f, -10.0f);
		Vector3 pos = Vector3(-11.0f, 5.0f, 0.0f);
		mCrackPos[0] = Vector3(220.0f, 0.0f, -0.5f);
		mCrackPos[1] = Vector3(-80.0f, -200, -0.5f);
		mCrackPos[2] = Vector3(-40.0f, 85.0f, -0.5f);
		mStartPos = Vector3(250.0f, -135.0f, -1.0f);

		object::Instantiate<Img_Stage0_Map>(Img_Stage0_Map::Stage0::forestfd02, pos, eLayerType::BGImg, this);
		object::Instantiate<Img_StartingPlate>(mStartPos, eLayerType::BGImg, this);

		GameObject* Forest02camera = object::Instantiate<GameObject>(cameraPos, eLayerType::BGImg, this);
		mCamera = Forest02camera->AddComp<Camera>();
		Forest02camera->AddComp<SCRIPT_MainCamera>();

		Img_Crack* crack0 = object::Instantiate<Img_Crack>(mCrackPos[0], eLayerType::BGImg, this);
		Img_Crack* crack1 = object::Instantiate<Img_Crack>(mCrackPos[1], eLayerType::BGImg, this);
		Img_Crack* crack2 = object::Instantiate<Img_Crack>(mCrackPos[2], eLayerType::BGImg, this);

		Vector3 gpos0 = Vector3(98.0f, 370.0f, -0.1f);
		Vector3 gpos1 = Vector3(135.0f, 370.0f, -0.1f);
		Vector3 gpos2 = Vector3(172.0f, 370.0f, -0.1f);

		mRewardPos = gpos1;

		mGate0 = object::Instantiate<Interact_Gate>(0, Vector3(98.0f, 370.0f, -0.1f), eLayerType::InteractableObject, this);
		mGate1 = object::Instantiate<Interact_Gate>(0, Vector3(135.0f, 370.0f, -0.1f), eLayerType::InteractableObject, this);
		mGate2 = object::Instantiate<Interact_Gate>(0, Vector3(172.0f, 370.0f, -0.1f), eLayerType::InteractableObject, this);

		mGate0->SetNextScene(L"05_Stage0_Forest03");
		mGate1->SetNextScene(L"05_Stage0_Forest03");
		mGate2->SetNextScene(L"05_Stage0_Forest03");

		gpos0.y += 20.0f;
		gpos1.y += 20.0f;
		gpos2.y += 20.0f;

		mItem0 = object::Instantiate<Item_AbilityEnhancer>(gpos0, eLayerType::Item, this);
		mItem1 = object::Instantiate<Item_AbilityEnhancer>(gpos1, eLayerType::Item, this);
		mItem2 = object::Instantiate<Item_AbilityEnhancer>(gpos2, eLayerType::Item, this);

		mRewardPos.y -= 80.0f;
		object::Instantiate<Img_RewardPlate>(mRewardPos, eLayerType::BGImg, this);


		//GameObject* mLight = new GameObject();
		//Light* mLg = mLight->AddComp<Light>();
		//AddGameObj(eLayerType::Light, mLight);
		//mLg->SetType(eLightType::Directional);
		//mLg->SetColor(mDayLight);

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
	void Stage0_Forest02::Update()
	{
		PlayScene::Update();
	}
	void Stage0_Forest02::LateUpdate()
	{
		PlayScene::LateUpdate();
	}
	void Stage0_Forest02::Render()
	{
		PlayScene::Render();
	}
	void Stage0_Forest02::OnEnter()
	{
		renderer::mainCamera = mCamera;

		PlayScene::OnEnter();

		const std::wstring path0 = { L"..\\Resources\\Tile\\forestfd02_00" };
		TilePalette::AutoLoad(path0);

		Player->GetComp<Transform>()->SetPosition(0.0f, 0.0f, 0.0f);

	}
	void Stage0_Forest02::OnExit()
	{
		mFocus->DeleteSelectobj(mGate0);
		mFocus->DeleteSelectobj(mGate1);
		mFocus->DeleteSelectobj(mGate2);
		PlayScene::OnExit();
	}
}