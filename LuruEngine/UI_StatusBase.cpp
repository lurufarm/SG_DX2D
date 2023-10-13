#include "UI_StatusBase.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "Gobj_Player.h"
#include "UI_CharBox.h"
#include "UI_FocusBoxes.h"
#include "Img_CharIcon.h"
#include "Img_BulletIcon.h"
#include "SCRIPT_UI.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	std::vector<UI_StatusBase::StatusSet*> UI_StatusBase::mStatuses = {};
	UI_FocusBoxes* UI_StatusBase::mFocus = nullptr;

	UI_StatusBase::UI_StatusBase()
	{
		mStatuses.clear();
	}
	UI_StatusBase::~UI_StatusBase()
	{
	}
	void UI_StatusBase::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		
		SetMesh();
		SetMaterial(L"UI_StatusBase");
		mMr->Initialize();
		mFocus = object::Instantiate<UI_FocusBoxes>(GetMyScene(), eLayerType::UI, GetMyScene());

		AddComp<SCRIPT_UI>();

	}
	void UI_StatusBase::Update()
	{
		Gobj_UI::Update();
	}
	void UI_StatusBase::LateUpdate()
	{
		Gobj_UI::LateUpdate();
	}
	void UI_StatusBase::Render()
	{
		Gobj_UI::Render();
	}

	void UI_StatusBase::MakeStatusSheet(Gobj_Character* character)
	{
		int characterNum = 99;
		std::wstring charName = character->GetName();
		if (charName == L"Cheese")
			characterNum = 0;
		else if (charName == L"Lucy")
			characterNum = 1;
		else if (charName == L"Robo")
			characterNum = 2;
		else if (charName == L"Szila")
			characterNum = 3;

		StatusSet* PlayerState = new StatusSet();
		mStatuses.push_back(PlayerState);
		Vector3 playerBoxPos = Vector3(-43.0f + (mStatuses.size() - 1 * 20.0f), 72.0f, -0.1f);
		Vector3 projIconPos = Vector3(-38.0f, 37.0f, -0.1f);

		PlayerState->charNum = characterNum;
		PlayerState->character = character;
		PlayerState->charIcon = object::Instantiate<Img_CharIcon>(characterNum, eLayerType::UI, SceneManager::GetActiveScene());
		PlayerState->bulletIcon = object::Instantiate<Img_BulletIcon>(characterNum, eLayerType::UI, SceneManager::GetActiveScene());
		PlayerState->charBox = object::Instantiate<UI_CharBox>(eLayerType::UI, SceneManager::GetActiveScene());

		PlayerState->charIcon->GetComp<Transform>()->SetPosition(playerBoxPos);
		PlayerState->bulletIcon->GetComp<Transform>()->SetPosition(projIconPos);
		PlayerState->charBox->GetComp<Transform>()->SetPosition(playerBoxPos);

		PlayerState->charIcon->AddComp<SCRIPT_UI>();
		PlayerState->bulletIcon->AddComp<SCRIPT_UI>();
		PlayerState->charBox->AddComp<SCRIPT_UI>();

		PlayerState->charBox->SetOrder(mStatuses.size() - 1);
		mFocus->AddSelectObj(PlayerState->charBox);
	}

}