#pragma once
#include "..\Engine_SOURCE\sgScene.h"
#include "Gobj_Monster.h"
#include "UI_FocusBoxes2.h"
#include <random>

namespace sg
{
	class PlayScene2 : public Scene
	{
	public:
		PlayScene2();
		~PlayScene2();

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
			std::uniform_int_distribution<>dist(0, 2);  // 0과 1 사이의 균등 분포
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
				for (auto iter = mPausedMobs.begin(); iter != mPausedMobs.end(); iter++)
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
		void CreateCompanyLight(class Gobj_Character* character);


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

		class Img_Crack* mCrack0;
		class Img_Crack* mCrack1;
		class Img_Crack* mCrack2;

		class Gobj_Light* mPlayerLight[4];
		int mLightnum = 1;

		Vector3 mCrackPos[3];
		Vector3 mStartPos;
		Vector3 mRewardPos;
		Vector3 mGatePos[3];

		static float mTime;
		static float mTime2;

		static bool mDay;
		Camera* mCamera;


		bool mClear = false;
		static class UI_FocusBoxes2* mFocus;

		std::random_device rd;
		std::mt19937 gen;
		class UI_StatusBase* mStatus;

	private:
		GameObject* mLight;
		Light* mLg;


	};
}
