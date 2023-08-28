#include "SCENE_PlayScene.h"
#include "..\Engine_SOURCE\sgTime.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgRenderer.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "..\Engine_SOURCE\sgCollisionManager.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "Gobj_Player.h"
#include "SCRIPT_Company.h"
#include "UI_FocusBoxes2.h"
#include "Gobj_Interactable.h"
#include "Interact_Gate.h"
#include <algorithm>
#include <random>

extern sg::Gobj_Player* Player;

namespace sg
{
	bool PlayScene::mDay = true;
	UI_FocusBoxes2* PlayScene::mFocus = nullptr;

	PlayScene::PlayScene()
	{
		SetName(L"PlayScene");
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		mTime = 0.0f;
		mTime2 = 0.0f;
		GameObject* mLight = new GameObject();
		mLg = mLight->AddComp<Light>();
		AddGameObj(eLayerType::Light, mLight);
		mLg->SetType(eLightType::Directional);
		mLg->SetColor(mDayLight);

		if (mFocus == nullptr)
			mFocus = object::Instantiate<UI_FocusBoxes2>(this, eLayerType::UI, this);
		
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::InteractableObject, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Tile, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster_Effect, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster_Bullet, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster_Bullet2, true);
		CollisionManager::SetLayer(eLayerType::Player_Bullet, eLayerType::Tile, true);
		CollisionManager::SetLayer(eLayerType::Player_Bullet, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Tile, true);
		CollisionManager::SetLayer(eLayerType::Monster_Bullet, eLayerType::Tile, true);
		CollisionManager::SetLayer(eLayerType::Monster_Bullet2, eLayerType::Tile, true);
		CollisionManager::SetLayer(eLayerType::Monster_Bullet, eLayerType::Effect, true);


		for (GameObject* mob : this->GetLayer(eLayerType::Monster).GetGameObjects())
		{
			Gobj_Monster* monster = dynamic_cast<Gobj_Monster*>(mob);
			mob->SetState(GameObject::eState::Paused);
			mPausedMobs.push_back(monster);
		}

		// º¤ÅÍ ¼¯±â
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(mPausedMobs.begin(), mPausedMobs.end(), g);

		Scene::Initialize();
	}
	void PlayScene::Update()
	{
		if (Input::KeyD(eKeyCode::B))
		{
			SceneManager::LoadScene(L"02_LobbyScene");
		}
		if (Input::KeyD(eKeyCode::P))
		{
			Gobj_Character* Lucy = SceneManager::GetChar(L"Lucy");
			Lucy->AddComp<SCRIPT_Company>();
			AddGameObj(eLayerType::Player, Lucy);
		}

		if (mActiveMobs.size() == 0 && mPausedMobs.size() == 0)
		{
			mGate0->Open();
			mGate1->Open();
			mGate2->Open();
		}

		if (mActiveMobs.size() < 5)
			SpawnMob();
		PurgeDeadMobs();

#pragma region test

		//mTime += Time::DeltaTime();
		//if (mTime > 5.0f)
		//	mTime2 += Time::DeltaTime();

		//if (mTime > 5.0f && mTime <= 7.0f)
		//{
		//	if (mTime2 >= 2.0f)
		//		mTime2 = 0.0f;

		//	Vector4 changecolor = Vector4::Lerp(mDayLight, mAfternoonLight, mTime2 / 2.0f);
		//	mLg->SetColor(changecolor);
		//}
		//else if (mTime > 7.0f && mTime <= 10.0f)
		//{
		//	mDay = false;
		//	mTime2 = 0.0f;
		//	mLg->SetColor(mAfternoonLight);
		//}
		//else if (mTime > 10.0f && mTime <= 12.0f)
		//{
		//	if (mTime2 >= 2.0f)
		//		mTime2 = 0.0f;

		//	Vector4 changecolor = Vector4::Lerp(mAfternoonLight, mEveningLight, mTime2 / 2.0f);
		//	mLg->SetColor(changecolor);

		//}
		//else if (mTime > 12.0f && mTime <= 15.0f)
		//{
		//	mTime2 = 0.0f;
		//	mLg->SetColor(mEveningLight);
		//}
		//else if (mTime > 15.0f && mTime <= 17.0f)
		//{
		//	if (mTime2 >= 2.0f)
		//		mTime2 = 0.0f;

		//	Vector4 changecolor = Vector4::Lerp(mEveningLight, mDawnLight, mTime2 / 2.0f);
		//	mLg->SetColor(changecolor);

		//}
		//else if (mTime > 17.0f && mTime <= 20.0f)
		//{
		//	mTime2 = 0.0f;
		//	mLg->SetColor(mDawnLight);
		//}
		//else if (mTime > 20.0f && mTime <= 22.0f)
		//{
		//	if (mTime2 >= 2.0f)
		//		mTime2 = 0.0f;
		//	mDay = true;
		//	Vector4 changecolor = Vector4::Lerp(mDawnLight, mDayLight, mTime2 / 2.0f);
		//	mLg->SetColor(changecolor);
		//}
		//else if (mTime > 22.0f)
		//{
		//	mTime = 0.0f;
		//	mLg->SetColor(mDayLight);
		//}

#pragma endregion

#pragma region realtime
		mTime += Time::DeltaTime();
		if (mTime > 500.0f)
			mTime2 += Time::DeltaTime();


		if (mTime > 500.0f && mTime <= 505.0f)
		{
			if (mTime2 >= 5.0f)
				mTime2 = 0.0f;

			Vector4 changecolor = Vector4::Lerp(mDayLight, mAfternoonLight, mTime2 / 5.0f);
			mLg->SetColor(changecolor);
		}
		else if (mTime > 505.0f && mTime <= 565.0f)
		{
			mDay = true;
			mTime2 = 0.0f;
			mLg->SetColor(mAfternoonLight);
		}
		else if (mTime > 565.0f && mTime <= 570.0f)
		{
			if (mTime2 >= 5.0f)
				mTime2 = 0.0f;

			Vector4 changecolor = Vector4::Lerp(mAfternoonLight, mEveningLight, mTime2 / 5.0f);
			mLg->SetColor(changecolor);

		}
		else if (mTime > 570.0f && mTime <= 870.0f)
		{
			mTime2 = 0.0f;
			mLg->SetColor(mEveningLight);
		}
		else if (mTime > 870.0f && mTime <= 880.0f)
		{
			if (mTime2 >= 10.0f)
				mTime2 = 0.0f;

			Vector4 changecolor = Vector4::Lerp(mEveningLight, mDawnLight, mTime2 / 10.0f);
			mLg->SetColor(changecolor);

		}
		else if (mTime > 880.0f && mTime <= 1180.0f)
		{
			mTime2 = 0.0f;
			mLg->SetColor(mDawnLight);
		}
		else if (mTime > 1180.0f && mTime <= 1200.0f)
		{
			mDay = false;
			if (mTime2 >= 20.0f)
				mTime2 = 0.0f;

			Vector4 changecolor = Vector4::Lerp(mDawnLight, mDayLight, mTime2 / 20.0f);
			mLg->SetColor(changecolor);
		}
		else if (mTime > 1200.0f)
		{
			mTime = 0.0f;
			mLg->SetColor(mDayLight);
		}
#pragma endregion

		Scene::Update();
	}
	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void PlayScene::Render()
	{
		Scene::Render();
	}
	void PlayScene::OnEnter()
	{
		renderer::lightsBuffer->Clear();
		float bgcolor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
		GetDevice()->SetBgColor(bgcolor);
		AddGameObj(eLayerType::Player, Player);
		AddGameObj(eLayerType::UI, mFocus);
		AddGameObj(eLayerType::UI, mFocus->mBoxes[0]);
		AddGameObj(eLayerType::UI, mFocus->mBoxes[1]);
		AddGameObj(eLayerType::UI, mFocus->mBoxes[2]);
		AddGameObj(eLayerType::UI, mFocus->mBoxes[3]);
		for (GameObject* interact : this->GetLayer(eLayerType::InteractableObject).GetGameObjects())
		{
			Gobj_Interactable* interactable = dynamic_cast<Gobj_Interactable*>(interact);
			mFocus->AddSelectObj(interactable);
		}
	}
	void PlayScene::OnExit()
	{
		DeleteGameObj(eLayerType::Player, Player);
		DeleteGameObj(eLayerType::UI, mFocus);
		DeleteGameObj(eLayerType::UI, mFocus->mBoxes[0]);
		DeleteGameObj(eLayerType::UI, mFocus->mBoxes[1]);
		DeleteGameObj(eLayerType::UI, mFocus->mBoxes[2]);
		DeleteGameObj(eLayerType::UI, mFocus->mBoxes[3]);
		//mFocus->clearObjs();
	}
}