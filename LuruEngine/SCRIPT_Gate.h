#pragma once
#include "..\Engine_SOURCE\sgScript.h"

namespace sg
{
	class SCRIPT_Gate : public Script
	{
	public:
		SCRIPT_Gate();
		~SCRIPT_Gate();

		virtual void Initialize();
		virtual void Update();

		virtual void OnCollisionEnter(Collider2D* other);
		virtual void OnCollisionStay(Collider2D* other);
		virtual void OnCollisionExit(Collider2D* other);

	private:
		class Interact_Gate* mOwner;
		class Gobj_Item* mItem;
	};
}
