#pragma once
#include "..\Engine_SOURCE\sgScript.h"

namespace sg
{
	class SCRIPT_CharSelect : public Script
	{
	public:
		SCRIPT_CharSelect();
		~SCRIPT_CharSelect();

		virtual void Initialize();
		virtual void Update();

		virtual void OnCollisionEnter(Collider2D* other);
		virtual void OnCollisionStay(Collider2D* other);
		virtual void OnCollisionExit(Collider2D* other);

	private:
		class GameObject* mOwner;
		static class UI_CharSelect* mObject;
	};
}
