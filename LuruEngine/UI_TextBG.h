#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"

namespace sg
{
	class UI_TextBG : public GameObject
	{
	public:
		UI_TextBG(float size);
		~UI_TextBG();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void SetTextBGSize(float f) { mSize = f; }
		float GetTextBGSize() { return mSize; }
		class Img_TextBG_left* GetTextBGL() { return mLeft; }
		class Img_TextBG_middle* GetTextBGM() { return mMiddle; }
		class Img_TextBG_right* GetTextBGR() { return mRight; }

	private:

		Transform* mTr;

		class Img_TextBG_left* mLeft;
		class Img_TextBG_middle* mMiddle;
		class Img_TextBG_right* mRight;

		float mSize;
		Vector3 mSize2;

	};
}
