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
		mPlayer = new Nemo();
		mPlayer->SetName(L"player");
		mGameObjects.push_back(mPlayer);

		for (size_t i = 0; i < 30; i++)
		{
			Enemy* newenemy = new Enemy();
			newenemy->SetName(L"enemy");
			mGameObjects.push_back(newenemy);
		}
	}
	void Scene::Update()
	{
			Vector2 nemoPos = Vector2(mPlayer->GetStat().mPos.x, mPlayer->GetStat().mPos.y);
			float nemoScale = mPlayer->GetStat().mScale;

			
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
				int a = 0;
			if (gameObj->GetName() == L"enemy")
			{
				Enemy* enemy = dynamic_cast<Enemy*>(gameObj);
				Vector2 enemyPos = Vector2(enemy->GetStat().mPos.x, enemy->GetStat().mPos.y);
				float enemyScale = enemy->GetStat().mScale;

				if (fabs(enemyPos.x - nemoPos.x) < (enemyScale)+(nemoScale)
					&& fabs(enemyPos.y - nemoPos.y) < (enemyScale)+(nemoScale))
				{
					//gameObj->SetState(GameObject::eState::Dead);
					mPlayer->SetScale(nemoScale + enemyScale / 2.0f);//), Vector3(nemoPos.x, nemoPos.y, 0.0f), mPlayer->GetStat().mColor);
					enemy->mDeath = true;

					if (enemy->mDeath && enemy->GetStat().mScale != 0.0f)
					{
						enemy->SetStat(0.0f, Vector3(enemyPos.x, enemyPos.y, 0.0f), Vector4::Zero);
						enemy->mEnemynum--;
					}

				}
			}
				gameObj->Update();
		}
			if (Enemy::mEnemynum <= 25)
			{
				for (size_t i = 0; i < 5; i++)
				{
					Enemy* newenemy = new Enemy();
					newenemy->SetName(L"enemy");
					mGameObjects.push_back(newenemy);
				}
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