#pragma once
#include "..\Engine_SOURCE\sgScript.h"
#include "Gobj_Player.h"

namespace sg
{
	class SCRIPT_MainCamera : public Script
	{
	public:
		virtual void Initialize();
		virtual void Update();

	private:

		Gobj_Player* mPlayer;

	};
};

