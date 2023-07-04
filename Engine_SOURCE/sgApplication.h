#pragma once
#include "LuruEngine.h"
#include "sgGraphicDevice_Dx11.h"
#include "sgScene.h"

namespace sg
{
	class Application
	{
	public:

		Application();
		~Application();

		void Run();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void SetWindow(HWND hwnd, UINT width, UINT height);

		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		HWND GetHwnd() { return mHwnd; }

	private:

		bool mbInitialize = false;
		// ���� �� ���� ��ü�� ���� �� �ִ� ����Ʈ ������
		std::unique_ptr<sg::graphics::GraphicDevice_Dx11> graphicDevice;

		// HDC mHDC -> GUI API
		HWND mHwnd;
		UINT mWidth;
		UINT mHeight;

	};

}
