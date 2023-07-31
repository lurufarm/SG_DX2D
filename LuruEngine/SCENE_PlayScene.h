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

	protected:
		bool mClear;
		GameObject* mLight;
		Light* mLg;

		Vector4 mDayLight = Vector4(0.8f, 0.8f, 0.8f, 1.0f);
		Vector4 mAfternoonLight = Vector4(0.5f, 0.3f, 0.2f, 1.0f);
		Vector4 mEveningLight = Vector4(0.1f, 0.2f, 0.4f, 1.0f);
		Vector4 mDawnLight = Vector4(0.3f, 0.3f, 0.5f, 1.0f);

		float mTime = 0.0f;
		float mTime2 = 0.0f;

		static bool mDay;
		Camera* mCamera;

	private:
	};
}
