#pragma once
#include "sgGameObject.h"
#include "sgRenderer.h"

using namespace sg::math;
using namespace renderer;
namespace sg
{

	class Enemy : public GameObject
	{
	public:
		Enemy();
		~Enemy();

		struct eEnemyStat
		{
			float mScale;
			Vector3 mPos;
			Vector4 mColor;
		};

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void SetStat(float scale, Vector3 pos, Vector4 color)
		{
			mStat.mScale = scale;
			mStat.mPos = pos;
			mStat.mColor = color;
		}

		eEnemyStat GetStat()
		{
			return mStat;
		}

		static int mEnemynum;
		bool mDeath;

	private:
		eState mState;

		eEnemyStat mStat;



	};
}
