#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgLight.h"

namespace sg
{
	class Gobj_Light : public GameObject
	{
	public:
		Gobj_Light();
		~Gobj_Light();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void SetLightType(eLightType lty) { mType = lty; }
		void SetLightRadius(float rad) { mRad = rad; }
		void SetLightColor(Vector4 color) 
		{ 
			mDefaultColor = color;
			mCo = color;
		}

		void SetLightOff()
		{
			mDefaultColor = mCo;
			mCo = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
		}
		void SetLightOn()
		{
			mCo = mDefaultColor;
		}
		void SetTarget(GameObject* target) { mTarget = target; }

		void SetLightOnOff(bool first, bool second, float time);

	private:

		Transform* mTr;
		Light* mLg;
		eLightType mType;
		float mRad;
		Vector4 mCo;
		Vector4 mDefaultColor;

		GameObject* mTarget;

		float mTime;

	};
}
