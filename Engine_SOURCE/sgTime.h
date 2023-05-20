#pragma once
#include "LuruEngine.h"

namespace sg
{
	class Time
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		__forceinline static double DeltaTime() { return mDeltaTime; }

	private:
		static double mDeltaTime;
		static double mSecond;
		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;
	};
};

