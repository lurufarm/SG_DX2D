#pragma once
#include "..\Engine_SOURCE\sgScript.h"

namespace sg
{
	class SCRIPT_CharInfo : public Script
	{
	public:
		SCRIPT_CharInfo(int num);
	
		void Initialize();
		void Update();
	private:
		class Gobj_Font* mOwner;
		class Gobj_Character* mChar;
	};
};

