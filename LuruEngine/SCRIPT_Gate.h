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

		Vector3 WorldPosToScreen(const Vector3 pos)
		{
			Viewport viewport = {};
			viewport.width = 1600.0f;
			viewport.height = 900.0f;
			viewport.x = 0;
			viewport.y = 0;
			viewport.minDepth = 0.0f;
			viewport.maxDepth = 1.0f;

			Vector3 screenPos = viewport.Project(pos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);

			return screenPos;
		};

	private:
		class Interact_Gate* mOwner;
		class Gobj_Item* mItem;
		class UI_TextBG* mTextBG;
	};
}
