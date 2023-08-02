#pragma once
#include "LuruEngine.h"
#include "sgMath.h"

namespace sg
{
	using namespace sg::math;

	enum class eKeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,

		UP, DOWN, LEFT, RIGHT, SPACE,
		LBUTTON, RBUTTON, ENTER,
		END,
	};

	enum class eKeyState
	{
		Down,
		Pressed,
		Up,
		None,
	};


	class Input
	{
	public:

		struct Key
		{
			eKeyCode key;
			eKeyState state;
			bool bPressed;
		};

		static void Initialize();
		static void Update();
		static void Render();

		inline static eKeyState GetKeyState(eKeyCode keyCode)
		{
			return mKeys[(UINT)keyCode].state;
		}

		static __forceinline bool KeyP(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Pressed;
		}

		static __forceinline bool KeyD(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Down;
		}

		static __forceinline bool KeyU(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Up;
		}

		static __forceinline Vector3 GetMousePos() { return mMousePos; }
		static __forceinline Vector3 GetMousePos2() { return mMousePos2; }

		static __forceinline Vector3 MousePosUnProject();

		static __forceinline Vector3 GetFinalMousePos() { return mFinalMousePos; }

		static __forceinline Key GetInputKeyA() { return mKeys[(UINT)eKeyCode::A]; }
		static __forceinline Key GetInputKeyD() { return mKeys[(UINT)eKeyCode::D]; }
		static __forceinline Key GetInputKeyW() { return mKeys[(UINT)eKeyCode::W]; }
		static __forceinline Key GetInputKeyS() { return mKeys[(UINT)eKeyCode::S]; }

		static __forceinline bool GetAnyKey()
		{
			for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
			{
				if (mKeys[i].state == eKeyState::Down || mKeys[i].state == eKeyState::Pressed)
				{
					return true;
				}
			}
			return false;
		}
		static __forceinline Key GetAnyKeyInfo()
		{
			for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
			{
				if (mKeys[i].state == eKeyState::Down || mKeys[i].state == eKeyState::Pressed)
				{
					return mKeys[i];
				}
			}
			return mKeys[(UINT)eKeyCode::END];
		}

	private:

		static std::vector<Key> mKeys;
		static Vector3 mMousePos;
		static Vector3 mMousePos2;
		static Vector3 mFinalMousePos;

	};

}
