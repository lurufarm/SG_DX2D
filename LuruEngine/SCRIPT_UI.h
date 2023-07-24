#pragma once
#include "..\Engine_SOURCE\sgScript.h"

namespace sg
{
	class SCRIPT_UI : public Script
	{
	public:
		virtual void Initialize();
		virtual void Update();

	private:
		class Gobj_Player* mPlayer;
		Vector3 mOwnerPos;

	};
}
