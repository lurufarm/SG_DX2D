#pragma once
#include "..\Engine_SOURCE\sgScene.h"
#include "Gobj_Monster.h"
#include "Gobj_Light.h"
#include "UI_FocusBoxes2.h"
#include <random>

namespace sg
{
	class Gobj_Light;
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		~PlayScene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnEnter();
		virtual void OnExit();

		static bool GetTime() { return mDay; }

		bool IsFinished()
		{
			if (mPausedMobs.empty() && mActiveMobs.empty())
				return true;
			else
				return false;
		}

		UINT SelectPos()
		{
			std::random_device rd;  // 랜덤 시드를 얻기 위한 장치
			std::mt19937 gen(rd());  // 메르센 트위스터 난수 생성기 초기화
			std::uniform_int_distribution<> dist(0, 2);  // 0과 1 사이의 균등 분포

			return dist(gen);
		}
		
		void InitializeItemIds();
		class Gobj_Item* MakeItem(Vector3 pos);
		Vector3 RandPos();

		void SpawnMob()
		{
			if (mPausedMobs.size() > 8)
			{
				for (auto iter = mPausedMobs.begin(); iter < mPausedMobs.begin() + 8; iter++)
				{
					(*iter)->SetState(GameObject::eState::Active);
					(*iter)->GetComp<Transform>()->SetPosition(RandPos());
					mActiveMobs.push_back(*iter);
					mFocus->AddSelectObj(*iter);
				}
				mPausedMobs.erase(mPausedMobs.begin(), mPausedMobs.begin() + 8);
			}
			else
			{
				for (auto iter = mPausedMobs.begin();iter != mPausedMobs.end();iter++)
				{
					(*iter)->SetState(GameObject::eState::Active);
					mActiveMobs.push_back(*iter);
					mFocus->AddSelectObj(*iter);
				}
				mPausedMobs.clear();
			}
		}


		void PurgeDeadMobs()
		{
			for (auto iter = mActiveMobs.begin(); iter != mActiveMobs.end();)
			{
				if ((*iter)->GetState() != GameObject::eState::Active)
				{
					GameObject* toDelete = *iter;
					iter = mActiveMobs.erase(iter);
					mFocus->DeleteSelectobj(toDelete);
				}
				else
				{
					iter++;
				}
			}
		}

		int SelectedItemID;

		void ChangeLight();

		Light* CreateCompanyLight(class Gobj_Character* character);

		class UI_StatusBase* GetStatusBase() { return mStatus; }

	protected:
		
		std::vector<class Gobj_Monster*> mPausedMobs;
		std::vector<class Gobj_Monster*> mActiveMobs;

		class Interact_Gate* mGate0;
		class Interact_Gate* mGate1;
		class Interact_Gate* mGate2;

		class Gobj_Item* mItem0;
		class Gobj_Item* mItem1;
		class Gobj_Item* mItem2;

		std::vector<int> mEnhenceItemIDs;
		std::vector<int> mCharItemIDs;

		Gobj_Light* mPlayerLight[4];
		int mLightnum = 1;

		Vector3 mCrackPos[3];
		Vector3 mStartPos;
		Vector3 mRewardPos;
		Vector3 mGatePos[3];

		const Vector4 mDayLight = Vector4(0.8f, 0.8f, 0.8f, 1.0f);
		const Vector4 mAfternoonLight = Vector4(0.5f, 0.3f, 0.2f, 1.0f);
		const Vector4 mEveningLight = Vector4(0.1f, 0.2f, 0.4f, 1.0f);
		const Vector4 mDawnLight = Vector4(0.3f, 0.3f, 0.5f, 1.0f);

		static float mTime;
		static float mTime2;

		static bool mDay;
		Camera* mCamera;
		

		bool mClear = false;
		static class UI_FocusBoxes2* mFocus;

		std::random_device rd;
		std::mt19937 gen;
		class UI_StatusBase* mStatus;
		Gobj_Light* mDLight;


	private:
		//Light* mLg;



	};
}
