#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"

namespace gui
{
	class GUI_EditorObject : public sg::GameObject
	{
	public:
		GUI_EditorObject();
		virtual	~GUI_EditorObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
	};
}