#include "sgApplication.h"

#include "sgInput.h"
#include "sgTime.h"
#include "sgRenderer.h"
#include "sgSceneManager.h"
#include "sgCollisionManager.h"

namespace sg
{
	Application::Application()
		: graphicDevice(nullptr)
		, mHwnd(NULL)
		, mWidth(-1)
		, mHeight(-1)
	{
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
	}
	void Application::Initialize()
	{
		Time::Initialize(); 
		Input::Initialize();

		renderer::Initialize();
		SceneManager::Initialize();
	}
	void Application::Update()
	{
		Time::Update();
		Input::Update();
		SceneManager::Update();
		CollisionManager::Update();
	}
	void Application::LateUpdate()
	{
		SceneManager::LateUpdate();
	}
	void Application::Render()
	{
		Time::Render();

		graphicDevice->ClearTarget();
		graphicDevice->UpdateViewPort();

		//SceneManager::Render();
		renderer::Render();
		//graphicDevice->Draw();

	}
	void Application::Destroy()
	{
		SceneManager::Destroy();
	}
	void Application::Present()
	{
		graphicDevice->Present();
	}
	void Application::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (graphicDevice == nullptr)
		{
			mHwnd = hwnd;
			mWidth = width;
			mHeight = height;

			graphicDevice = std::make_unique<sg::graphics::GraphicDevice_Dx11>();
			sg::graphics::GetDevice() = graphicDevice.get();
		}

		RECT rt = { 0, 0, (LONG)width, (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);

	}
}