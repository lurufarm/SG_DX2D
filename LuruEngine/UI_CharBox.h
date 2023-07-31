#pragma once
#include "Gobj_UI.h"

namespace sg
{
	class UI_CharBox : public Gobj_UI
	{
	public:
		UI_CharBox();
		~UI_CharBox();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();
		
		void SetCharNum(int num) { mCharNum = num; }
		int GetCharNum() { return mCharNum; }

	private:
		UINT mCharNum;
		Collider2D* mCol;

	};
}
