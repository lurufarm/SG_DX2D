#pragma once
#include "..\Engine_SOURCE\sgScript.h"

namespace sg
{
	class SCRIPT_TextBG : public Script
	{
	public:
		virtual void Initialize();
		virtual void Update();

	private:
		class Gobj_Player* mPlayer;
		class UI_TextBG* mOwner;

		class Img_TextBG_left* mLeft;
		class Img_TextBG_middle* mMiddle;
		class Img_TextBG_right* mRight;

		Vector3 mLeftPos;
		Vector3 mMiddlePos;
		Vector3 mRightPos;

	};
}
