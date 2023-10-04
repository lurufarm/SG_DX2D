#pragma once
#include "LuruEngine.h"

#include "..\\External\\FW1FontWrapper\\Include\\FW1FontWrapper.h"
#include "..\\External\\FW1FontWrapper\\Include\\FW1CompileSettings.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\FW1FontWrapper\\Library\\Debug\\FW1FontWrapperL.lib")
#else
#pragma comment(lib, "..\\External\\FW1FontWrapper\\Library\\Debug\\FW1FontWrapper.lib")
#endif


namespace sg
{
#define FONT_RGBA(r, g, b, a) (((((BYTE)a << 24 ) | (BYTE)b << 16) | (BYTE)g << 8) | (BYTE)r)

	class FontWrapper
	{
	public:
		static bool Initialize();
		static void Render();
		static void Release();

		static void DrawFont(const WCHAR* str, float x, float y, float size, UINT rgb);
		static void SetFontOption(float x, float y, float size, UINT rgb);
		static WCHAR mText[100];

	private:
		static IFW1Factory* mFW1Factory;
		static IFW1FontWrapper* mFontWrapper;

		static float mXpos;
		static float mYpos;
		static float mFontSize;
		static UINT mFontColor;
	};
}
