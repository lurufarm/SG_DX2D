#pragma once
#include "..\Engine_SOURCE\CommonInclude.h"
#include "..\Engine_SOURCE\LuruEngine.h"
#include "..\Engine_SOURCE\sgGraphics.h"

#include "GUI_Widget.h"
#include "GUI_EditorObject.h"
#include "GUI_DebugObject.h"


namespace gui
{
	class GUI_Editor
	{
	public:
		static void Initialize();
		static void Run();

		static void Update();
		static void LateUpdate();
		static void Render();
		static void Release();

		static void DebugRender(const sg::graphics::DebugMesh& mesh);
		
	private:
		static std::vector<GUI_Widget*> mWidgets;
		static std::vector<GUI_EditorObject*> mEditorObjects;
		static std::vector<GUI_DebugObject*> mDebugObjects;
	};
}