#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"

namespace gui
{
	class GUI_DebugObject : public sg::GameObject
	{
	public:
		GUI_DebugObject();
		~GUI_DebugObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}