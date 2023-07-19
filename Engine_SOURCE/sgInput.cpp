#include "sgInput.h"
#include "sgApplication.h"

extern sg::Application application;

namespace sg
{
	using namespace sg::math;

	int ASCII[(UINT)eKeyCode::END] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',

		VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_SPACE,
		VK_LBUTTON, VK_RBUTTON, VK_RETURN,
	};

	std::vector<Input::Key> Input::mKeys;
	Vector3 Input::mMousePos = Vector3::Zero;
	Vector3 Input::mFinalMousePos = Vector3::Zero;

	void Input::Initialize()
	{

		for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
		{
			Key keyInfo;
			keyInfo.key = (eKeyCode)i;
			keyInfo.state = eKeyState::None;
			keyInfo.bPressed = false;

			mKeys.push_back(keyInfo);
		}
	}
	void Input::Update()
	{
		if (GetFocus())
		{
			for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
			{
				if (GetAsyncKeyState(ASCII[i]) & 0x8000)
				{
					// ���� �����ӵ� ���� �ִ� ���
					if (mKeys[i].bPressed)
						mKeys[i].state = eKeyState::Pressed;
					// ó�� ���� ���
					else
						mKeys[i].state = eKeyState::Down;
					
					mKeys[i].bPressed = true;
				}
				else // ���� �����ӿ� Ű�� �������� ���� ���
				{
					// ���� �����ӿ��� Ű�� �����ִ� ���
					if (mKeys[i].bPressed)
						mKeys[i].state = eKeyState::Up;
					else
						mKeys[i].state = eKeyState::None;
					
					mKeys[i].bPressed = false;
				}
			}

			POINT mousePos = {};
			GetCursorPos(&mousePos);
			ScreenToClient(application.GetHwnd(), &mousePos);

			mMousePos.x = mousePos.x;
			mMousePos.y = mousePos.y;
			mMousePos.z = 0.0f;

			MousePosUnProject();
		}
		else
		{
			for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
			{
				if (eKeyState::Down == mKeys[i].state
					|| eKeyState::Pressed == mKeys[i].state)
					mKeys[i].state = eKeyState::Up;
				else if (eKeyState::Up == mKeys[i].state)
					mKeys[i].state = eKeyState::None;

				mKeys[i].bPressed = false;
			}
		}
	}
	void Input::Render()
	{
	}
	Vector3 Input::MousePosUnProject()
	{
		POINT mousePos = {};
		GetCursorPos(&mousePos);
		ScreenToClient(application.GetHwnd(), &mousePos);

		Vector3 tempPos = {};

		tempPos.x = mousePos.x;
		tempPos.y = mousePos.y;
		tempPos.z = 0.0f;

		Viewport viewport = {};

		viewport.width = 1600.0f;
		viewport.height = 900.0f;
		viewport.x = 0;
		viewport.y = 0;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		mFinalMousePos = viewport.Unproject(tempPos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);

		return mFinalMousePos;
	}
}