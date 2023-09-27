#include "GUI_Editor.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgRenderer.h"
#include "..\Engine_SOURCE\sgResources.h"
#include "..\Engine_SOURCE\sgMesh.h"
#include "..\Engine_SOURCE\sgMaterial.h"

#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgMeshRenderer.h"

#include "..\LuruEngine\Tile_TilePalette.h"

#include "SCRIPT_GridScript.h"

namespace gui
{
	using namespace sg::enums;

	std::vector<GUI_Widget*> GUI_Editor::mWidgets = {};
	std::vector<GUI_EditorObject*> GUI_Editor::mEditorObjects = {};
	std::vector<GUI_DebugObject*> GUI_Editor::mDebugObjects = {};
	bool GUI_Editor::mOn = true;

	void GUI_Editor::Initialize()
	{
		mDebugObjects.resize((UINT)eColliderType::End);

		std::shared_ptr <sg::Mesh> mesh
			= sg::Resources::Find<sg::Mesh>(L"DebugRect");
		std::shared_ptr<sg::Material> material
			= sg::Resources::Find<sg::Material>(L"DebugMaterial");

		mDebugObjects[(UINT)eColliderType::Rect] = new GUI_DebugObject();
		mDebugObjects[(UINT)eColliderType::Rect]->AddComp<sg::Transform>();
		sg::MeshRenderer* mr = mDebugObjects[(UINT)eColliderType::Rect]
			->AddComp<sg::MeshRenderer>();
		mr->SetMaterial(material);
		mr->SetMesh(mesh);

		//GUI_EditorObject* grid = new GUI_EditorObject();
		//grid->SetName(L"Grid");

		//mr = grid->AddComp<sg::MeshRenderer>();
		//mr->SetMesh(sg::Resources::Find<sg::Mesh>(L"RectMesh"));
		//mr->SetMaterial(sg::Resources::Find<sg::Material>(L"GridMaterial"));
		//sg::SCRIPT_GridScript* gridscript = grid->AddComp<sg::SCRIPT_GridScript>();
		//gridscript->SetCamera(renderer::cameras[0]);

		//mEditorObjects.push_back(grid);
	}

	void GUI_Editor::Run()
	{
		Update();
		LateUpdate();
		Render();
	}
	void GUI_Editor::Update()
	{
		if (sg::Input::KeyD(sg::eKeyCode::O))
		{
			if (mOn)
				mOn = false;
			else if (mOn == false)
				mOn = true;
		}

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
		if (mOn)
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
			renderer::debugMeshs.clear();
		}
	}

	void GUI_Editor::Release()
	{
		for (auto widget : mWidgets)
		{
			delete widget;
			widget = nullptr;
		}
		for (auto editorObj : mEditorObjects)
		{
			delete editorObj;
			editorObj = nullptr;
		}
		for (auto debugObj : mDebugObjects)
		{
			delete debugObj;
			debugObj = nullptr;
		}
	}

	void GUI_Editor::DebugRender(const sg::graphics::DebugMesh& mesh)
	{
		GUI_DebugObject* debugObj = mDebugObjects[(UINT)mesh.type];

		// 위치, 크기, 회전 정보를 받아와서
		// 해당 게임 오브젝트 위에 그려준다.

		sg::Transform* tr = debugObj->GetComp<sg::Transform>();

		Vector3 pos = mesh.position;
		pos.z -= 0.01f;

		tr->SetPosition(pos);
		tr->SetScale(mesh.scale);
		tr->SetRotation(0.0f, 0.0f, mesh.rotation.z);

		tr->LateUpdate();
		
		renderer::MyCB mycb = {};
		mycb.ColliderColor = mesh.MyCBType;
		mycb.TileIndex = sg::TilePalette::GetIndex();

		ConstantBuffer* MyCB = renderer::constantBuffer[(UINT)eCBType::MyCBType];
		MyCB->SetData(&mycb);
		MyCB->Bind(eShaderStage::PS);
		
		sg::Camera* mainCamera = renderer::mainCamera;

		sg::Camera::SetGpuViewMatrix(mainCamera->GetViewMatrix());
		sg::Camera::SetGpuProjectionMatrix(mainCamera->GetProjectionMatrix());

		debugObj->Render();
	}
	void GUI_Editor::DebugUpdate(const sg::graphics::DebugMesh& mesh)
	{
		GUI_DebugObject* debugObj = mDebugObjects[(UINT)mesh.type];
		debugObj->LateUpdate();
	}
}