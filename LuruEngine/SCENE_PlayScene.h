#pragma once
#include "..\Engine_SOURCE\sgScene.h"

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
			if (mSceneMob.empty())
				return true;
			else
				return false;
		}

	protected:
		
		std::vector<class Gobj_Monster*> mSceneMob;

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
