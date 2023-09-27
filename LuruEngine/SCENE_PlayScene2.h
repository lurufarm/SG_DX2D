#pragma once
#include "..\Engine_SOURCE\sgScene.h"
#include "Gobj_Monster.h"
#include "Gobj_Light.h"
#include "UI_FocusBoxes2.h"
#include <random>

namespace sg
{
	class Gobj_Light;
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
			std::random_device rd;  // ���� �õ带 ��� ���� ��ġ
			std::mt19937 gen(rd());  // �޸��� Ʈ������ ���� ������ �ʱ�ȭ
			std::uniform_int_distribution<> dist(0, 2);  // 0�� 1 ������ �յ� ����

			return dist(gen);
		}

		class Gobj_Item* MakeItem(Vector3 pos);

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

		Vector3 RandPos();

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

		Gobj_Light* mPlayerLight[4];
		int mLightnum = 1;

		Vector3 mCrackPos[3];
		Vector3 mStartPos;
		Vector3 mRewardPos;

		const Vector4 mDayLight = Vector4(0.7f, 0.7f, 0.7f, 1.0f);
		const Vector4 mAfternoonLight = Vector4(0.5f, 0.3f, 0.2f, 1.0f);
		const Vector4 mEveningLight = Vector4(0.1f, 0.2f, 0.4f, 1.0f);
		const Vector4 mDawnLight = Vector4(0.3f, 0.3f, 0.5f, 1.0f);

		static float mTime;
		static float mTime2;

		static bool mDay;
		Camera* mCamera;


		bool mClear = false;
		static class UI_FocusBoxes2* mFocus;

	private:
		GameObject* mLight;
		Light* mLg;

	};
}
