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

		struct eNemoStat
		{
			float mScale;
			Vector3 mPos;
			Vector4 mColor;
		};

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void SetNemo(class Nemo* nemo)
		{
			mNemo = nemo;
		}

		void SetStat(float scale, Vector3 pos, Vector4 color)
		{
			mStat.mScale = scale;
			mStat.mPos = pos;
			mStat.mColor = color;
		}

		eNemoStat GetStat()
		{
			return mStat;
		}

		static int mNemonum;

	private:
		eState mState;

		eNemoStat mStat;

		Vertex mSquare[4];

		class Mesh* mMesh;
		class Shader* mShader;

		class Nemo* mNemo;


	};
}
