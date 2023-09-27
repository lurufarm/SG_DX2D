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

extern sg::Gobj_Player* Player;

namespace sg
{
	bool PlayScene2::mDay = false;
	float PlayScene2::mTime = 0.0f;
	float PlayScene2::mTime2 = 0.0f;
	UI_FocusBoxes2* PlayScene2::mFocus = nullptr;

	PlayScene2::PlayScene2()
	{
	}
	PlayScene2::~PlayScene2()
	{
	}
	void PlayScene2::Initialize()
	{
		GameObject* mLight = new GameObject();
		mLg = mLight->AddComp<Light>();
		AddGameObj(eLayerType::Light, mLight);
		mLg->SetType(eLightType::Directional);
		mLg->SetColor(mEveningLight);
		//mLg->SetColor(Vector4::Zero);

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

		if (mItem0)
		{
			mItem0->SetState(GameObject::eState::Paused);
			mItem1->SetState(GameObject::eState::Paused);
			mItem2->SetState(GameObject::eState::Paused);

			mGate0->SetItem(mItem0);
			mGate1->SetItem(mItem1);
			mGate2->SetItem(mItem2);

			mGate0->AddComp<SCRIPT_Gate>();
			mGate1->AddComp<SCRIPT_Gate>();
			mGate2->AddComp<SCRIPT_Gate>();
		}
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

		// 벡터 섞기
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(mPausedMobs.begin(), mPausedMobs.end(), g);

		if (mPlayerLight[0] == nullptr)
		{
			mPlayerLight[0] = object::Instantiate<Gobj_Light>(eLayerType::Light, this);
			mPlayerLight[0]->SetTarget(Player);
			mPlayerLight[0]->SetLightType(eLightType::Point);
			mPlayerLight[0]->SetLightRadius(30.0f);
			mPlayerLight[0]->SetLightColor(Vector4(0.6f, 0.4f, 0.2f, 0.8f));
		}
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
		mTime += Time::DeltaTime();
		//ChangeLight();

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

		float bgcolor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
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
		//renderer::lightsBuffer->Clear();

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
	Gobj_Item* PlayScene2::MakeItem(Vector3 pos)
	{

		std::random_device rd;  // 랜덤 시드를 얻기 위한 장치
		std::mt19937 gen(rd());  // 메르센 트위스터 난수 생성기 초기화
		std::uniform_int_distribution<> dist(0, 9);  // 0과 1 사이의 균등 분포

		int a = dist(gen);

		if (a <= 4)
		{
			return object::Instantiate<Item_AbilityEnhancer>(pos, eLayerType::Item, this);
		}
		else if (a > 4)
		{
			return object::Instantiate<Item_Chars>(pos, eLayerType::Item, this);
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
	void PlayScene2::ChangeLight()
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
			mLg->SetColor(changecolor);
		}
		else if (mTime > 65.0f && mTime <= 125.0f)
		{
			for (size_t i = 0; i < mLightnum; i++)
			{
				mPlayerLight[i]->SetLightOn();
			}
			mTime2 = 0.0f;
			mLg->SetColor(mAfternoonLight);
		}
		else if (mTime > 125.0f && mTime <= 130.0f)
		{
			if (mTime2 >= 5.0f)
				mTime2 = 0.0f;

			Vector4 changecolor = Vector4::Lerp(mAfternoonLight, mEveningLight, mTime2 / 5.0f);
			mLg->SetColor(changecolor);

		}
		else if (mTime > 130.0f && mTime <= 190.0f)
		{
			mTime2 = 0.0f;
			mLg->SetColor(mEveningLight);
		}
		else if (mTime > 190.0f && mTime <= 200.0f)
		{
			if (mTime2 >= 10.0f)
				mTime2 = 0.0f;

			Vector4 changecolor = Vector4::Lerp(mEveningLight, mDawnLight, mTime2 / 10.0f);
			mLg->SetColor(changecolor);

		}
		else if (mTime > 200.0f && mTime <= 260.0f)
		{
			mTime2 = 0.0f;
			mLg->SetColor(mDawnLight);
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
			mLg->SetColor(changecolor);
		}
		else if (mTime > 280.0f)
		{
			mTime = 0.0f;
			mLg->SetColor(mDayLight);
		}
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