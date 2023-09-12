#include "SCRIPT_CharSelect.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgObject.h"

#include "SCENE_LobbyScene.h"

#include "UI_CharBox.h"
#include "UI_CharSelect.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	UI_CharSelect* SCRIPT_CharSelect::mObject = nullptr;
	SCRIPT_CharSelect::SCRIPT_CharSelect()
	{
	}
	SCRIPT_CharSelect::~SCRIPT_CharSelect()
	{
	}
	void SCRIPT_CharSelect::Initialize()
	{
		mOwner = (GameObject*)GetOwner();
	}
	void SCRIPT_CharSelect::Update()
	{
		if (mObject == nullptr)
		{
			mObject = object::Instantiate<UI_CharSelect>(eLayerType::UI, SceneManager::GetActiveScene());
			mObject->SetState(GameObject::eState::Paused);
		}


		if (Input::KeyD(eKeyCode::ENTER))
		{
			if (mObject->GetState() == GameObject::eState::Paused)
			{
				if (mOwner->GetSelected())
				{
					mObject->SetState(GameObject::eState::Active);
					LobbyScene::FocusBoxesPaused();
				}
			}
			else if (mObject->GetState() == GameObject::eState::Active)
			{
				if (mObject->GetBoxes(0, 0)->GetSelected())
				{
					Player->SetChar(SceneManager::GetChar(L"Cheese"));
					mObject->SetState(GameObject::eState::Paused);
					LobbyScene::FocusBoxesActive();
				}
				else if (mObject->GetBoxes(0, 1)->GetSelected())
				{
					Player->SetChar(SceneManager::GetChar(L"Lucy"));
					mObject->SetState(GameObject::eState::Paused);
					LobbyScene::FocusBoxesActive();
				}
				else if (mObject->GetBoxes(0, 2)->GetSelected())
				{
					Player->SetChar(SceneManager::GetChar(L"Robo"));
					mObject->SetState(GameObject::eState::Paused);
					LobbyScene::FocusBoxesActive();
				}
			}
		}

		if (Input::KeyD(eKeyCode::X))
		{
			if (mObject->GetState() == GameObject::eState::Active)
			{
				mObject->SetState(GameObject::eState::Paused);
				LobbyScene::FocusBoxesActive();
			}
		}
	}
	void SCRIPT_CharSelect::OnCollisionEnter(Collider2D* other)
	{
	}
	void SCRIPT_CharSelect::OnCollisionStay(Collider2D* other)
	{
	}
	void SCRIPT_CharSelect::OnCollisionExit(Collider2D* other)
	{
	}
}