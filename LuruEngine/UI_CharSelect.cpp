#include "UI_CharSelect.h"
#include "..\Engine_SOURCE\sgObject.h"

#include "UI_CharBox.h"
#include "UI_FocusBoxes.h"

#include "Gobj_Player.h"

#include "SCRIPT_UI.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	UI_CharSelect::UI_CharSelect()
	{
		std::wstring name = Gobj_UI::GetName();
		name += L"_CharSelect";
		SetName(name);

		UI_CharSelect::Initialize();
	}
	UI_CharSelect::~UI_CharSelect()
	{
		for (size_t i = 0; i < 2; i++)
		{
			for (size_t j = 0; j < 5; j++)
			{
				object::Destroy(mBoxes[i][j]);
			}
		}
		//object::Destroy(mFocus);
		//delete mFocus;
		SceneManager::GetActiveScene()->DeleteGameObj(eLayerType::UI, mFocus);
		object::Destroy(mFocus);
	}
	void UI_CharSelect::Initialize()
	{
		mTr = GetComp<Transform>();
		mTr->SetPosition(0.0f, 0.0f, -5.0f);
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		//SetMaterial(L"AnimationMaterial");
		SetMaterial(L"UICharSelect");
		mFocus = object::Instantiate<UI_FocusBoxes>(SceneManager::GetActiveScene(), eLayerType::UI, SceneManager::GetActiveScene());

		int order = 1;
		for (size_t i = 0; i < 2; i++)
		{
			for (size_t j = 0; j < 5; j++)
			{
				Vector3 boxpos = {};
				boxpos.y = (i * -20.0f) + 40.0f;
				boxpos.x = j * 20.0f - 40.0f;
				boxpos.z = -3.0f;
				mBoxes[i][j] = object::Instantiate<UI_CharBox>(boxpos, eLayerType::UI, SceneManager::GetActiveScene());
				mBoxes[i][j]->AddComp<SCRIPT_UI>();
				mBoxes[i][j]->SetOrder(order);
				order++;
				mFocus->AddSelectObj(mBoxes[i][j]);
			}
		}
		mMr->Initialize();
		mFocus->SetSelectObj(mBoxes[0][0]);
	
		AddComp<SCRIPT_UI>();

	}
	void UI_CharSelect::Update()
	{
		Gobj_UI::Update();

		for (size_t i = 0; i < 2; i++)
		{
			for (size_t j = 0; j < 5; j++)
			{
				mBoxes[i][j]->SetState(this->GetState());
			}
		}
		mFocus->SetState(this->GetState());

	}
	void UI_CharSelect::LateUpdate()
	{
		Gobj_UI::LateUpdate();
	}
	void UI_CharSelect::Render()
	{
		Gobj_UI::Render();
	}
}