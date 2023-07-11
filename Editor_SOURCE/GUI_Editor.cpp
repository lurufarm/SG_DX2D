#include "GUI_Editor.h"
#include "sgRenderer.h"
#include "sgResources.h"
#include "sgMesh.h"
#include "sgMaterial.h"

#include "sgTransform.h"
#include "sgMeshRenderer.h"

#include "SCRIPT_GridScript.h"

namespace gui
{
	using namespace sg::enums;

	std::vector<GUI_Widget*> GUI_Editor::mWidgets = {};
	std::vector<GUI_EditorObject*> GUI_Editor::mEditorObjects = {};
	std::vector<GUI_DebugObject*> GUI_Editor::mDebugObjects = {};

	void GUI_Editor::Initialize()
	{
		mDebugObjects.resize((UINT)eColliderType::End);

		std::shared_ptr<sg::Mesh> mesh
			= sg::Resources::Find<sg::Mesh>(L"DebugRect");
		std::shared_ptr<sg::Material> material
			= sg::Resources::Find<sg::Material>(L"DebugMaterial");

		mDebugObjects[(UINT)eColliderType::Rect] = new GUI_DebugObject();
		mDebugObjects[(UINT)eColliderType::Rect]->AddComp<sg::Transform>();
		sg::MeshRenderer* mr = mDebugObjects[(UINT)eColliderType::Rect]
			->AddComp<sg::MeshRenderer>();
		mr->SetMaterial(material);
		mr->SetMesh(mesh);

		GUI_EditorObject* grid = new GUI_EditorObject();
		grid->SetName(L"Grid");

		mr = grid->AddComp<sg::MeshRenderer>();
		mr->SetMesh(sg::Resources::Find<sg::Mesh>(L"RectMesh"));
		mr->SetMaterial(sg::Resources::Find<sg::Material>(L"GridMaterial"));
		sg::SCRIPT_GridScript* gridscript = grid->AddComp<sg::SCRIPT_GridScript>();
		gridscript->SetCamera(renderer::cameras[0]);

		mEditorObjects.push_back(grid);
	}

	void GUI_Editor::Run()
	{
		Update();
		LateUpdate();
		Render();
	}
	void GUI_Editor::Update()
	{
		for (GUI_EditorObject* Eobj : mEditorObjects)
		{
			Eobj->Update();
		}
	}
	void GUI_Editor::LateUpdate()
	{
		for (GUI_EditorObject* Eobj : mEditorObjects)
		{
			Eobj->LateUpdate();
		}

	}
	void GUI_Editor::Render()
	{
		for (GUI_EditorObject* Eobj : mEditorObjects)
		{
			Eobj->Render();
		}

		for (const sg::graphics::DebugMesh& mesh
			: renderer::debugMeshs)
		{
			DebugRender(mesh);
		}
	}
	void GUI_Editor::Release()
	{
	}
	void GUI_Editor::DebugRender(const sg::graphics::DebugMesh& mesh)
	{
		GUI_DebugObject* debugObj = mDebugObjects[(UINT)mesh.type];

		// 위치, 크기, 회전 정보를 받아와서
		// 해당 게임 오브젝트 위에 그려준다.
		
		debugObj->Render();
	}
}