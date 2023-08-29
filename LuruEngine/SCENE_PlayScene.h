#pragma once
#include "..\Engine_SOURCE\sgScene.h"
#include "Gobj_Monster.h"
#include "UI_FocusBoxes2.h"
#include <random>

namespace sg
{
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
			if (mPausedMobs.empty())
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
		
		void SpawnMob()
		{
			if (mPausedMobs.size() > 8)
			{
				for (auto iter = mPausedMobs.begin(); iter < mPausedMobs.begin() + 8; iter++)
				{
					(*iter)->SetState(GameObject::eState::Active);
					(*iter)->GetComp<Transform>()->SetPosition(mCrackPos[SelectPos()]);
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

	protected:
		
		std::vector<class Gobj_Monster*> mPausedMobs;
		std::vector<class Gobj_Monster*> mActiveMobs;

		class Interact_Gate* mGate0;
		class Interact_Gate* mGate1;
		class Interact_Gate* mGate2;

		Vector3 mCrackPos[3];
		Vector3 mStartPos;

		const Vector4 mDayLight = Vector4(0.6f, 0.6f, 0.6f, 1.0f);
		const Vector4 mAfternoonLight = Vector4(0.5f, 0.3f, 0.2f, 1.0f);
		const Vector4 mEveningLight = Vector4(0.1f, 0.2f, 0.4f, 1.0f);
		const Vector4 mDawnLight = Vector4(0.3f, 0.3f, 0.5f, 1.0f);

		float mTime = 0.0f;
		float mTime2 = 0.0f;

		static bool mDay;
		Camera* mCamera;

		static class UI_FocusBoxes2* mFocus;

	private:
		GameObject* mLight;
		Light* mLg;

	};
}
