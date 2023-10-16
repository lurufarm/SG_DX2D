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
	}
	UI_StatusBase::~UI_StatusBase()
	{
	}
	void UI_StatusBase::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		
		SetMesh();
		SetMaterial(L"UIStatusBase");
		//SetMaterial(L"TransparentMaterial");
		mMr->Initialize();
		mFocus = object::Instantiate<UI_FocusBoxes>(GetMyScene(), eLayerType::UI_Box, GetMyScene());
		AddComp<SCRIPT_UI>();

	}
	void UI_StatusBase::Update()
	{
		for (size_t i = 0; i < mStatuses.size(); i++)
		{
			if (mStatuses[i]->charBox->GetSelected())
			{
				mStatuses[i]->charIcon->SetSelected(true);
				if (this->GetState() == Active)
					mStatuses[i]->bulletIcon->SetState(Active);
			}
			else
			{
				mStatuses[i]->charIcon->SetSelected(false);
				mStatuses[i]->bulletIcon->SetState(Paused);
			}
		}

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
		Vector3 playerBoxPos = Vector3(-44.0f + (mStatuses.size() - 1) * 20.0f, 72.0f, -1.2f);
		Vector3 projIconPos = Vector3(-38.0f, 37.0f, -1.2f);

		PlayerState->charNum = characterNum;
		PlayerState->character = character;
		PlayerState->charIcon = object::Instantiate<Img_CharIcon>(characterNum, eLayerType::UI_Box, this->GetMyScene());
		PlayerState->bulletIcon = object::Instantiate<Img_BulletIcon>(characterNum, eLayerType::UI_Box, this->GetMyScene());
		PlayerState->charBox = object::Instantiate<UI_CharBox>(eLayerType::UI_Box, this->GetMyScene());

		PlayerState->charIcon->GetComp<Transform>()->SetPosition(playerBoxPos);
		PlayerState->bulletIcon->GetComp<Transform>()->SetPosition(projIconPos);
		PlayerState->charBox->GetComp<Transform>()->SetPosition(playerBoxPos);

		PlayerState->charIcon->AddComp<SCRIPT_UI>();
		PlayerState->bulletIcon->AddComp<SCRIPT_UI>();
		PlayerState->charBox->AddComp<SCRIPT_UI>();

		PlayerState->charBox->SetOrder(mStatuses.size());
		mFocus->AddSelectObj(PlayerState->charBox);
		mFocus->SetSelectObj(mStatuses[0]->charBox);

		StateUpdate();
	}

	void UI_StatusBase::StateUpdate()
	{
		mFocus->SetState(GetState());
		mFocus->mBoxes[0]->SetState(GetState());
		mFocus->mBoxes[1]->SetState(GetState());
		mFocus->mBoxes[2]->SetState(GetState());
		mFocus->mBoxes[3]->SetState(GetState());
		for (size_t i = 0; i < mStatuses.size(); i++)
		{
			mStatuses[i]->charBox->SetState(GetState());
			mStatuses[i]->charIcon->SetState(GetState());
			mStatuses[i]->bulletIcon->SetState(GetState());
		}
	}
	void UI_StatusBase::SceneUpdate()
	{
		Scene* now = SceneManager::GetActiveScene();
		now->DeleteGameObj(eLayerType::UI, this);
		now->DeleteGameObj(eLayerType::UI_Box, mFocus);
		now->DeleteGameObj(eLayerType::UI_Box, mFocus->mBoxes[0]);
		now->DeleteGameObj(eLayerType::UI_Box, mFocus->mBoxes[1]);
		now->DeleteGameObj(eLayerType::UI_Box, mFocus->mBoxes[2]);
		now->DeleteGameObj(eLayerType::UI_Box, mFocus->mBoxes[3]);
		for (size_t i = 0; i < mStatuses.size(); i++)
		{
			now->DeleteGameObj(eLayerType::UI, mStatuses[i]->charBox);
			now->DeleteGameObj(eLayerType::UI, mStatuses[i]->charIcon);
			now->DeleteGameObj(eLayerType::UI, mStatuses[i]->bulletIcon);
		}

		Scene* next = SceneManager::GetNextScene();
		next->AddGameObj(eLayerType::UI, this);
		next->AddGameObj(eLayerType::UI_Box, mFocus);
		next->AddGameObj(eLayerType::UI_Box, mFocus->mBoxes[0]);
		next->AddGameObj(eLayerType::UI_Box, mFocus->mBoxes[1]);
		next->AddGameObj(eLayerType::UI_Box, mFocus->mBoxes[2]);
		next->AddGameObj(eLayerType::UI_Box, mFocus->mBoxes[3]);
		for (size_t i = 0; i < mStatuses.size(); i++)
		{
			next->AddGameObj(eLayerType::UI, mStatuses[i]->charBox);
			next->AddGameObj(eLayerType::UI, mStatuses[i]->charIcon);
			next->AddGameObj(eLayerType::UI, mStatuses[i]->bulletIcon);
		}

	}

}