#include "sgScene.h"
#include "sgNemo.h"
#include "sgEnemy.h"

namespace sg
{
	Scene::Scene()
	{
	}
	Scene::~Scene()
	{
	}
	void Scene::Initialize()
	{
		//Nemo* nemo = new Nemo();
		//mGameObjects.push_back(nemo);
		Enemy* enemy[30] = {};
		mPlayer = new Nemo();
		mGameObjects.push_back(mPlayer);

		for (size_t i = 0; i < 10; i++)
		{
			enemy[i] = new Enemy();
			enemy[i]->SetName(L"enemy");
			enemy[i]->SetNemo(mPlayer);
			mGameObjects.push_back(enemy[i]);
		}
	}
	void Scene::Update()
	{
			Vector2 nemoPos = Vector2(mPlayer->GetStat().mPos.x, mPlayer->GetStat().mPos.y);
			float nemoScale = mPlayer->GetStat().mScale;

			
		for (GameObject* gameObj : mGameObjects)
		{
			Vector2 enemyPos = Vector2(((Enemy*)gameObj)->GetStat().mPos.x, ((Enemy*)gameObj)->GetStat().mPos.y);
			float enemyScale = ((Enemy*)gameObj)->GetStat().mScale;

			if (gameObj->GetName() == L"enemy")
			{
				if (fabs(enemyPos.x - nemoPos.x) < (enemyScale)+(nemoScale)
					&& fabs(enemyPos.y - nemoPos.y) < (enemyScale)+(nemoScale))
				{
					//gameObj->SetState(GameObject::eState::Dead);
					mPlayer->SetStat(nemoScale + enemyScale / 2, Vector3(nemoPos.x, nemoPos.y, 0.0f), mPlayer->GetStat().mColor);
					((Enemy*)gameObj)->SetStat(0.0f, Vector3::Zero, Vector4::Zero);
				}
			}
			gameObj->Update();
		}
	}
	void Scene::LateUpdate()
	{
	}
	void Scene::Render()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Render();
		}
	}
}