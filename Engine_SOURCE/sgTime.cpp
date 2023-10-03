#include "sgTime.h"
#include "sgApplication.h"
#include "sgRenderer.h"
#include "..\LuruEngine\Gobj_Player.h"
#include "sgFontWrapper.h"

extern sg::Application application;
extern sg::Gobj_Player* Player;

namespace sg
{
	double Time::mDeltaTime = 0.0l;
	double Time::mSecond = 0.0f;
	float Time::mTime = 0.0f;
	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};

	void Time::Initialize()
	{
		// CPU 고유 진동 수 가져오기
		QueryPerformanceFrequency(&mCpuFrequency);

		// 프로그램이 처음 시작할 때의 진동 수
		QueryPerformanceCounter(&mPrevFrequency);
	}

	void Time::Update()
	{
		QueryPerformanceCounter(&mCurFrequency);

		double differenceFrequency = mCurFrequency.QuadPart - mPrevFrequency.QuadPart;

		mDeltaTime = differenceFrequency / mCpuFrequency.QuadPart;
		
		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;

		mTime += mDeltaTime;
	}

	void Time::Render()
	{
		mSecond += mDeltaTime;

		if (mSecond > 1.0f)
		{
			HWND hwnd = application.GetHwnd();

			wchar_t szFloat[50] = {};
			float FPS = 1.0f / (float)mDeltaTime;
			Vector3 ppos = Player->GetComp<Transform>()->GetPosition();
			//swprintf_s(szFloat, 50, L"FPS : %d", (UINT)FPS);
			swprintf_s(szFloat, 50, L"X : %f, Y : %f, Z : %f", ppos.x, ppos.y, ppos.z);
			//int iLen = wcsnlen_s(szFloat, 50);
			SetWindowText(hwnd, szFloat);

			//TextOut(hdc, 0, 0, szFloat, 20);
			mSecond = 0.0;
		}
	}
	void Time::BindConstantBuffer()
	{
		renderer::TimeCB tmCB = {};
		tmCB.mTime.y = mTime;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Time];
		cb->SetData(&tmCB);
		cb->Bind(eShaderStage::PS);



	}
}