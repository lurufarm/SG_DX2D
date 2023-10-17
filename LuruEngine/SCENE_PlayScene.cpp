#include "SCENE_PlayScene.h"
#include "..\Engine_SOURCE\sgTime.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgRenderer.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "..\Engine_SOURCE\sgCollisionManager.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgFontWrapper.h"
#include "Gobj_Player.h"
#include "UI_FocusBoxes2.h"
#include "UI_HpBar.h"
#include "UI_HpBase.h"
#include "Img_Finish.h"
#include "Gobj_Interactable.h"
#include "Gobj_Light.h"
#include "Interact_Gate.h"
#include <algorithm>
#include <random>
#include "Item_AbilityEnhancer.h"
#include "Item_Chars.h"
#include "Item_Selected.h"
#include "SCRIPT_Company.h"
#include "SCRIPT_Gate.h"
#include "UI_StatusBase.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	bool PlayScene::mDay = true;
	float PlayScene::mTime = 0.0f;
	float PlayScene::mTime2 = 0.0f;
	UI_FocusBoxes2* PlayScene::mFocus = nullptr;

	PlayScene::PlayScene()
		: mDLight(nullptr)
		, gen(rd())
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		mStatus = SceneManager::GetStatusBase();

		mGatePos[0].y += 30.0f;
		mGatePos[1].y += 30.0f;
		mGatePos[2].y += 30.0f;

		InitializeItemIds();
		mItem0 = MakeItem(mGatePos[0]);
		mItem1 = MakeItem(mGatePos[1]);
		mItem2 = MakeItem(mGatePos[2]);

		mItem0->SetState(GameObject::eState::Paused);
		mItem1->SetState(GameObject::eState::Paused);
		mItem2->SetState(GameObject::eState::Paused);

		mGate0->SetItem(mItem0);
		mGate1->SetItem(mItem1);
		mGate2->SetItem(mItem2);

		mGate0->AddComp<SCRIPT_Gate>();
		mGate1->AddComp<SCRIPT_Gate>();
		mGate2->AddComp<SCRIPT_Gate>();
		if (mDLight == nullptr)
		{

			mDLight = object::Instantiate<Gobj_Light>(eLayerType::Light, this);
			mDLight->SetLightType(eLightType::Directional);
			mDLight->SetLightColor(mDayLight);
			//mLg = mDLight->GetComp<Light>();
			//AddGameObj(eLayerType::Light, mDLight);
			//mLg->SetType(eLightType::Directional);
			//mLg->SetColor(mDayLight);
		}

		if (mFocus == nullptr)
			mFocus = object::Instantiate<UI_FocusBoxes2>(this, eLayerType::UI, this);
		
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Player, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::InteractableObject, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Tile, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster_Effect, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster_Bullet, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster_Bullet2, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster_BulletBehindMonster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Item, true);
		CollisionManager::SetLayer(eLayerType::Player_Bullet, eLayerType::Tile, true);
		CollisionManager::SetLayer(eLayerType::Player_Bullet, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player_Beam, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Tile, true);
		CollisionManager::SetLayer(eLayerType::Monster_Bullet, eLayerType::Tile, true);
		CollisionManager::SetLayer(eLayerType::Monster_Bullet2, eLayerType::Tile, true);
		CollisionManager::SetLayer(eLayerType::Monster_BulletBehindMonster, eLayerType::Tile, true);
		CollisionManager::SetLayer(eLayerType::Monster_Bullet, eLayerType::Effect, true);


		object::Instantiate<UI_HPBase>(eLayerType::UI, this);
		object::Instantiate<UI_HPBar>(eLayerType::UI, this);

		for (GameObject* mob : this->GetLayer(eLayerType::Monster).GetGameObjects())
		{
			Gobj_Monster* monster = dynamic_cast<Gobj_Monster*>(mob);
			UI_HPBar* hpbar = object::Instantiate<UI_HPBar>(eLayerType::UI, this);
			hpbar->SetHPBarOwner(monster);
			mob->SetState(GameObject::eState::Paused);
			mPausedMobs.push_back(monster);
		}

		// ∫§≈Õ ºØ±‚
		std::shuffle(mPausedMobs.begin(), mPausedMobs.end(), gen);

		if (mPlayerLight[0] == nullptr)
		{
			mPlayerLight[0] = object::Instantiate<Gobj_Light>(eLayerType::Light, this);
			mPlayerLight[0]->SetTarget(Player);
			mPlayerLight[0]->SetLightType(eLightType::Point);
			mPlayerLight[0]->SetLightRadius(30.0f);
			mPlayerLight[0]->SetLightColor(Vector4(0.6f, 0.5f, 0.4f, 0.8f));
		}
		Scene::Initialize();
	}
	void PlayScene::Update()
	{
		mTime += Time::DeltaTime();

		if (Input::KeyD(eKeyCode::B))
		{
			SceneManager::LoadScene(L"02_LobbyScene");
		}
		
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
			mGate0->Open();
			mGate1->Open();
			mGate2->Open();
			object::Instantiate<Img_Finish>(eLayerType::UI_Box, this);
			mClear = true;
			if (mItem0)
			{
				mRewardPos.y += 10.0f;
				object::Instantiate<Item_Selected>(mRewardPos, eLayerType::Item, SceneManager::GetActiveScene());
			}
		}

		if (mActiveMobs.size() < 5)
			SpawnMob();
		PurgeDeadMobs();
		//ChangeLight();

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
		//mDLight->SetLightOff();
		//mDLight->SetLightOn();
		float bgcolor[4] = { 0.5f, 0.5f, 0.5f, 0.0f };
		GetDevice()->SetBgColor(bgcolor);

		AddGameObj(eLayerType::Player, Player);
		Player->GetComp<Transform>()->SetPosition(mStartPos);
		Player->Heal(1);
		for (Gobj_Character* company : Player->GetActiveCompanies())
		{
			AddGameObj(eLayerType::Player, company);
			Vector3 cpos = company->GetComp<SCRIPT_Company>()->RandPos(mStartPos);
			company->GetComp<Transform>()->SetPosition(cpos);
		}

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
		mStatus->SceneUpdate();

		DeleteGameObj(eLayerType::Player, Player);

		for (Gobj_Character* company : Player->GetActiveCompanies())
		{
			DeleteGameObj(eLayerType::Player, company);
		}
		for (GameObject* ui : this->GetLayer(eLayerType::UI).GetGameObjects())
		{
			DeleteGameObj(eLayerType::UI, ui);
		}

	}
	void PlayScene::InitializeItemIds()
	{
		mEnhenceItemIDs.clear();
		mCharItemIDs.clear();

		for (size_t i = 0; i < 12; i++)
		{
			mEnhenceItemIDs.push_back(i);
		}
		for (size_t i = 0; i < 4; i++)
		{
			mCharItemIDs.push_back(20 + i);
		}
	}
	Gobj_Item* PlayScene::MakeItem(Vector3 pos)
	{
		std::uniform_int_distribution<> dist(0, 9);
		int a = dist(gen);

		if (a <= 6) 
		{
			int index = std::uniform_int_distribution<>(0, mEnhenceItemIDs.size() - 1)(gen);
			int num = mEnhenceItemIDs[index];
			mEnhenceItemIDs.erase(mEnhenceItemIDs.begin() + index);
			return object::Instantiate<Item_AbilityEnhancer>(num, pos, eLayerType::Item, this);
		}
		else 
		{
			int index = std::uniform_int_distribution<>(0, mCharItemIDs.size() - 1)(gen);
			int num = mCharItemIDs[index];
			mCharItemIDs.erase(mCharItemIDs.begin() + index);
			return object::Instantiate<Item_Chars>(num, pos, eLayerType::Item, this);
		}
		//return object::Instantiate<Item_Chars>(22, pos, eLayerType::Item, this);
	}
	Vector3 PlayScene::RandPos()
	{
		const float PI = 3.141592;
		float angle = static_cast<float>(rand() / static_cast<float>(RAND_MAX) * 2 * PI);

		// random distance
		float distance = 30.0f;
		float randomDistance = static_cast<float>(rand() / static_cast<float>(RAND_MAX) * distance);

		// angle + distance
		Vector3 randomPos = mCrackPos[SelectPos()];
		randomPos.x += randomDistance * cos(angle);
		randomPos.y += randomDistance * sin(angle);
		randomPos.z = -0.6f;

		return randomPos;
	}
	void PlayScene::ChangeLight()
	{
		if (mTime < 65.0f)
		{
			for (size_t i = 0; i < mLightnum; i++)
			{
				mPlayerLight[i]->SetLightOff();
			}
		}

		if (mTime > 60.0f)
			mTime2 += Time::DeltaTime();


		if (mTime > 60.0f && mTime <= 65.0f)
		{
			if (mTime2 >= 5.0f)
				mTime2 = 0.0f;

			Vector4 changecolor = Vector4::Lerp(mDayLight, mAfternoonLight, mTime2 / 5.0f);
			//mLg->SetColor(changecolor);
			mDLight->SetLightColor(changecolor);
		}
		else if (mTime > 65.0f && mTime <= 125.0f)
		{
			for (size_t i = 0; i < mLightnum; i++)
			{
				mPlayerLight[i]->SetLightOn();
			}
			mTime2 = 0.0f;
			//mLg->SetColor(mAfternoonLight);
			mDLight->SetLightColor(mAfternoonLight);
		}
		else if (mTime > 125.0f && mTime <= 130.0f)
		{
			if (mTime2 >= 5.0f)
				mTime2 = 0.0f;

			Vector4 changecolor = Vector4::Lerp(mAfternoonLight, mEveningLight, mTime2 / 5.0f);
			//mLg->SetColor(changecolor);
			mDLight->SetLightColor(changecolor);
		}
		else if (mTime > 130.0f && mTime <= 190.0f)
		{
			mTime2 = 0.0f;
			//mLg->SetColor(mEveningLight);
			mDLight->SetLightColor(mEveningLight);
		}
		else if (mTime > 190.0f && mTime <= 200.0f)
		{
			if (mTime2 >= 10.0f)
				mTime2 = 0.0f;

			Vector4 changecolor = Vector4::Lerp(mEveningLight, mDawnLight, mTime2 / 10.0f);
			//mLg->SetColor(changecolor);
			mDLight->SetLightColor(changecolor);
		}
		else if (mTime > 200.0f && mTime <= 260.0f)
		{
			mTime2 = 0.0f;
			//mLg->SetColor(mDawnLight);
			mDLight->SetLightColor(mDawnLight);
		}
		else if (mTime > 260.0f && mTime <= 280.0f)
		{
			for (size_t i = 0; i < mLightnum; i++)
			{
				mPlayerLight[i]->SetLightOff();
			}
			if (mTime2 >= 20.0f)
				mTime2 = 0.0f;

			Vector4 changecolor = Vector4::Lerp(mDawnLight, mDayLight, mTime2 / 20.0f);
			//mLg->SetColor(changecolor);
			mDLight->SetLightColor(changecolor);

		}
		else if (mTime > 280.0f)
		{
			mTime = 0.0f;
			//mLg->SetColor(mDayLight);
			mDLight->SetLightColor(mDayLight);
		}
	}
	Light* PlayScene::CreateCompanyLight(Gobj_Character* character)
	{
		Light* companyLight;

		companyLight = character->AddComp<Light>();
		companyLight->SetType(eLightType::Point);
		companyLight->SetRadius(30.0f);
		companyLight->SetColor(Vector4(0.6f, 0.4f, 0.2f, 0.8f));

		return companyLight;
	}
}