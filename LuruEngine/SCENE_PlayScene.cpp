#include "SCENE_PlayScene.h"
#include "..\Engine_SOURCE\sgTime.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgRenderer.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "..\Engine_SOURCE\sgCollisionManager.h"
#include "Gobj_Player.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	bool PlayScene::mDay = true;

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

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::InteractableObject, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Tile, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster_Effect, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster_Bullet, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster_Bullet2, true);
		CollisionManager::SetLayer(eLayerType::Player_Bullet, eLayerType::Tile, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Tile, true);
		CollisionManager::SetLayer(eLayerType::Monster_Bullet, eLayerType::Tile, true);
		CollisionManager::SetLayer(eLayerType::Monster_Bullet2, eLayerType::Tile, true);
		CollisionManager::SetLayer(eLayerType::Monster_Bullet, eLayerType::Effect, true);

		for (GameObject* mob : this->GetLayer(eLayerType::Monster).GetGameObjects())
		{
			Gobj_Monster* monster = dynamic_cast<Gobj_Monster*>(mob);
			mSceneMob.push_back(monster);
		}

		Scene::Initialize();
	}
	void PlayScene::Update()
	{
		if (Input::KeyD(eKeyCode::B))
		{
			SceneManager::LoadScene(L"02_LobbyScene");
		}

		for (Gobj_Monster* mob : mSceneMob)
		{
			if (mob->GetState() == GameObject::eState::Dead || mob == nullptr)
			{
				std::vector<Gobj_Monster*>::iterator iter =
					mSceneMob.begin();
				for (;iter != mSceneMob.end();iter++)
				{
					if (mob == *iter)
					{
						mSceneMob.erase(iter);
					}
				}
			}
		}


#pragma region test

		mTime += Time::DeltaTime();
		if (mTime > 5.0f)
			mTime2 += Time::DeltaTime();

		if (mTime > 5.0f && mTime <= 7.0f)
		{
			if (mTime2 >= 2.0f)
				mTime2 = 0.0f;

			Vector4 changecolor = Vector4::Lerp(mDayLight, mAfternoonLight, mTime2 / 2.0f);
			mLg->SetColor(changecolor);
		}
		else if (mTime > 7.0f && mTime <= 10.0f)
		{
			mDay = false;
			mTime2 = 0.0f;
			mLg->SetColor(mAfternoonLight);
		}
		else if (mTime > 10.0f && mTime <= 12.0f)
		{
			if (mTime2 >= 2.0f)
				mTime2 = 0.0f;

			Vector4 changecolor = Vector4::Lerp(mAfternoonLight, mEveningLight, mTime2 / 2.0f);
			mLg->SetColor(changecolor);

		}
		else if (mTime > 12.0f && mTime <= 15.0f)
		{
			mTime2 = 0.0f;
			mLg->SetColor(mEveningLight);
		}
		else if (mTime > 15.0f && mTime <= 17.0f)
		{
			if (mTime2 >= 2.0f)
				mTime2 = 0.0f;

			Vector4 changecolor = Vector4::Lerp(mEveningLight, mDawnLight, mTime2 / 2.0f);
			mLg->SetColor(changecolor);

		}
		else if (mTime > 17.0f && mTime <= 20.0f)
		{
			mTime2 = 0.0f;
			mLg->SetColor(mDawnLight);
		}
		else if (mTime > 20.0f && mTime <= 22.0f)
		{
			if (mTime2 >= 2.0f)
				mTime2 = 0.0f;
			mDay = true;
			Vector4 changecolor = Vector4::Lerp(mDawnLight, mDayLight, mTime2 / 2.0f);
			mLg->SetColor(changecolor);
		}
		else if (mTime > 22.0f)
		{
			mTime = 0.0f;
			mLg->SetColor(mDayLight);
		}

#pragma endregion

#pragma region realtime
		/*mTime += Time::DeltaTime();
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
		}*/
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
		//renderer::lightsBuffer->Clear();
		float bgcolor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
		GetDevice()->SetBgColor(bgcolor);
		AddGameObj(eLayerType::Player, Player);
	}
	void PlayScene::OnExit()
	{
		DeleteGameObj(eLayerType::Player, Player);
	}
}