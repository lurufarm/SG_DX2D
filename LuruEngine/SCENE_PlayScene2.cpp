#include "SCENE_PlayScene2.h"

#include "..\Engine_SOURCE\sgTime.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgRenderer.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "..\Engine_SOURCE\sgCollisionManager.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "Gobj_Player.h"
#include "SCRIPT_Company.h"
#include "SCRIPT_Gate.h"
#include "UI_FocusBoxes2.h"
#include "Gobj_Interactable.h"
#include "Gobj_Light.h"
#include "Interact_Gate.h"
#include <algorithm>
#include <random>
#include "Item_AbilityEnhancer.h"
#include "Item_Chars.h"
#include "Item_Selected.h"
#include "UI_HpBar.h"
#include "UI_HpBase.h"
#include "Img_Crack.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	bool PlayScene2::mDay = false;
	float PlayScene2::mTime = 0.0f;
	float PlayScene2::mTime2 = 0.0f;
	UI_FocusBoxes2* PlayScene2::mFocus = nullptr;

	PlayScene2::PlayScene2()
		: gen(rd())
	{
	}
	PlayScene2::~PlayScene2()
	{
	}
	void PlayScene2::Initialize()
	{
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

		if (mLight == nullptr)
		{
			mLight = new GameObject();
			mLg = mLight->AddComp<Light>();
			mLg->SetType(eLightType::Directional);
			mLg->SetColor(Vector4(0.2f, 0.2f, 0.2f, 1.0f));
			AddGameObj(eLayerType::Light, mLight);
		}

		mGatePos[0].y += 30.0f;
		mGatePos[1].y += 30.0f;
		mGatePos[2].y += 30.0f;

		if (mFocus == nullptr)
			mFocus = object::Instantiate<UI_FocusBoxes2>(this, eLayerType::UI, this);

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

		mCrack0->GetComp<Light>()->SetColor(Vector4(0.5f, 0.4f, 0.3f, 0.3f));
		mCrack1->GetComp<Light>()->SetColor(Vector4(0.5f, 0.4f, 0.3f, 0.3f));
		mCrack2->GetComp<Light>()->SetColor(Vector4(0.5f, 0.4f, 0.3f, 0.3f));

		Scene::Initialize();
	}
	void PlayScene2::Update()
	{
		if (Input::KeyD(eKeyCode::B))
		{
			SceneManager::LoadScene(L"02_LobbyScene");
		}

		if (mActiveMobs.size() == 0 && mPausedMobs.size() == 0 && mClear == false)
		{
			mGate0->Open();
			mGate1->Open();
			mGate2->Open();
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

		Scene::Update();
	}
	void PlayScene2::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void PlayScene2::Render()
	{
		Scene::Render();
	}
	void PlayScene2::OnEnter()
	{
		renderer::lightsBuffer->Clear();

		float bgcolor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GetDevice()->SetBgColor(bgcolor);

		AddGameObj(eLayerType::Player, Player);
		Player->GetComp<Transform>()->SetPosition(mStartPos);

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
	void PlayScene2::OnExit()
	{
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
	void PlayScene2::InitializeItemIds()
	{
		mEnhenceItemIDs.clear();
		mCharItemIDs.clear();

		for (size_t i = 0; i < 12; i++)
		{
			mEnhenceItemIDs.push_back(i);
		}
		for (size_t i = 0; i < 3; i++)
		{
			mCharItemIDs.push_back(20 + i);
		}
	}
	Gobj_Item* PlayScene2::MakeItem(Vector3 pos)
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
		//return object::Instantiate<Item_Chars>(pos, eLayerType::Item, this);
	}
	Vector3 PlayScene2::RandPos()
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
		randomPos.z = -0.1f;

		return randomPos;
	}
	void PlayScene2::CreateCompanyLight(Gobj_Character* character)
	{
		mPlayerLight[mLightnum] = object::Instantiate<Gobj_Light>(eLayerType::Light, this);
		mPlayerLight[mLightnum]->SetTarget(character);
		mPlayerLight[mLightnum]->SetLightRadius(30.0f);
		mPlayerLight[mLightnum]->SetLightColor(Vector4(0.6f, 0.4f, 0.2f, 0.8f));
		mLightnum++;
	}
}