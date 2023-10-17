#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgFontWrapper.h"

namespace sg
{
	class Gobj_Font : public GameObject
	{
	public:
		Gobj_Font();
		~Gobj_Font();
		
		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void SetFontOption(float x, float y, float size, UINT rgb);
		void SetText(const wchar_t text[]);
		std::wstring GetText() { return mText; }
		Vector3 GetFontOption()	{return Vector3(mXpos, mYpos, mFontSize); }
		UINT GetFontColor() { return mFontColor; }

	private:

		Transform* mTr;

		IFW1Factory* mFW1Factory;
		IFW1FontWrapper* mFontWrapper;

		WCHAR mText[100];
		float mXpos;
		float mYpos;
		float mFontSize;
		UINT mFontColor;

	};

}