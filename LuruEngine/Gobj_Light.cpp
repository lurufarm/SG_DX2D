#include "Gobj_Light.h"
#include "..\Engine_SOURCE\sgTime.h"

namespace sg
{
	Gobj_Light::Gobj_Light()
		: mType(eLightType::Point)
		, mRad(0.0f)
		, mCo(Vector4::Zero)
	{
		mLg = AddComp<Light>();
		mTr = GetComp<Transform>();
		mTarget = nullptr;
	}
	Gobj_Light::~Gobj_Light()
	{
	}
	void Gobj_Light::Initialize()
	{
	}
	void Gobj_Light::Update()
	{
		mTime += Time::DeltaTime();

		mLg->SetType(mType);
		mLg->SetColor(mCo);

		if (mType == eLightType::Point)
			mLg->SetRadius(mRad);

		if (mTarget)
		{
			mTr->SetPosition(mTarget->GetComp<Transform>()->GetPosition());
		}

		GameObject::Update();
	}
	void Gobj_Light::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Gobj_Light::Render()
	{
		GameObject::Render();
	}
	void Gobj_Light::SetLightOnOff(bool first, bool second, float time)
	{
		if (first && second == false) // Àá±ñ ÄÑÁ³´Ù°¡ ²¨Áü
		{
			if (mTime <= time)
			{
				mCo = Vector4::Zero;
			}
			else
			{
				mCo = mDefaultColor;
			}
		}
		else if (first == false && second) // Àá±ñ ²¨Á³´Ù°¡ ÄÑÁü
		{
			if (mTime <= time)
			{
				mCo = mDefaultColor;
			}
			else
			{
				mCo = Vector4::Zero;
			}
		}
		else if (first == second) //µÎ °ªÀÌ °°À» °æ¿ì¿¡´Â ±ôºý±ôºý°Å¸®´Â È¿°ú
		{
			
		}
	
	}
}