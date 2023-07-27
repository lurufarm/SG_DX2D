#include "SCENE_PlayScene.h"
#include "..\Engine_SOURCE\sgTime.h"

namespace sg
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		mLight = new GameObject();
		mLg = mLight->AddComp<Light>();
		AddGameObj(eLayerType::Light, mLight);
		mLg->SetType(eLightType::Directional);
		mLg->SetColor(mDayLight);


		Scene::Initialize();
	}
	void PlayScene::Update()
	{

		mTime += Time::DeltaTime();
		mTime2 += Time::DeltaTime();

		
		if (mTime > 4.0f && mTime <= 7.0f)
		{
			if (mTime2 >= 3.0f)
				mTime2 = 0.0f;

			Vector4 changecolor = Vector4::Lerp(mDayLight, mAfternoonLight, mTime2 / 3.0f);
			mLg->SetColor(changecolor);
		}
		else if (mTime > 7.0f && mTime <= 10.0f)
		{
			if (mTime2 >= 3.0f)
				mTime2 = 0.0f;

			Vector4 changecolor = Vector4::Lerp(mAfternoonLight, mEveningLight, mTime2 / 3.0f);
			mLg->SetColor(changecolor);
		}
		else if (mTime > 10.0f && mTime <= 12.0f)
		{

			if (mTime2 >= 2.0f)
				mTime2 = 0.0f;

			Vector4 changecolor = Vector4::Lerp(mEveningLight, mDawnLight, mTime2 / 2.0f);
			mLg->SetColor(changecolor);
		}
		else if (mTime > 12.0f && mTime <= 13.0f)
		{

			if (mTime2 >= 1.0f)
				mTime2 = 0.0f;

			Vector4 changecolor = Vector4::Lerp(mDawnLight, mDayLight, mTime2);
			mLg->SetColor(changecolor);
		}
		if (mTime >= 15.0f)
		{
			mTime = 0.0f;
			mTime2 = 0.0f;
		}

#pragma region Changing Light by Time
		if (mTime > 480.0f && mTime <= 720.0f)
		{
			float t = mTime / 240;

			Vector4 changecolor = Vector4::Lerp(mDayLight, mAfternoonLight, t);
			mLg->SetColor(changecolor);
		}
		else if (mTime > 720.0f && mTime <= 1020.0f)
		{
			float t = mTime / 300.0f;

			Vector4 changecolor = Vector4::Lerp(mAfternoonLight, mEveningLight, t);
			mLg->SetColor(changecolor);
		}
		else if (mTime > 1020.0f && mTime <= 1200.0f)
		{
			float t = mTime / 180.0f;

			Vector4 changecolor = Vector4::Lerp(mEveningLight, mDawnLight, t);
			mLg->SetColor(changecolor);
		}
		else if (mTime > 1200.0f && mTime <= 1300.0f)
		{
			float t = mTime / 100.0f;
			Vector4 changecolor = Vector4::Lerp(mDawnLight, mDayLight, t);
			mLg->SetColor(changecolor);
		}
		if (mTime >= 1600.0f)
		{
			mTime = 0.0f;
		}

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
	}
	void PlayScene::OnExit()
	{
	}
}