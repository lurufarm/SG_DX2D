#include "SCRIPT_Gate.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "..\Engine_SOURCE\sgFontWrapper.h"
#include "SCENE_PlayScene.h"
#include "SCENE_PlayScene2.h"
#include "Interact_Gate.h"
#include "Item_AbilityEnhancer.h"
#include "Gobj_Item.h"

namespace sg
{
	SCRIPT_Gate::SCRIPT_Gate()
	{
	}
	SCRIPT_Gate::~SCRIPT_Gate()
	{
	}
	void SCRIPT_Gate::Initialize()
	{
		mOwner = (Interact_Gate*)GetOwner();
	}
	void SCRIPT_Gate::Update()
	{
		mItem = mOwner->GetItem();

		if (mOwner->GetIsOpen())
		{
			mItem->SetState(GameObject::eState::Active);

			if (mOwner->GetSelected())
			{

				//wcscpy_s(FontWrapper::mText, L"Test");
				//FontWrapper::SetFontOption(800, 400, 20.0f, FONT_RGBA(255, 0, 255, 255));


				//FontWrapper::DrawFont(L"�߰� ����", 10, 30, 20, FONT_RGBA(255, 0, 255, 255));

				int itemID = mItem->GetItemID();
				switch (itemID)
				{
				case 0:
					break;
				case 1 :
					break;
					
				default:
					break;
				}
			}

			if (mOwner->GetSelected() && Input::KeyD(eKeyCode::N))
			{
				Scene* sc = SceneManager::LoadNextScene();
				PlayScene* ps = dynamic_cast<PlayScene*>(sc);
				if (ps != nullptr)
				{
					ps->SelectedItemID = mItem->GetItemID();
				}
				else
				{
					PlayScene2* ps2 = dynamic_cast<PlayScene2*>(sc);
					ps2->SelectedItemID = mItem->GetItemID();
				}
					mItem->SetItemActivate(true);
			}
		}
	}
	void SCRIPT_Gate::OnCollisionEnter(Collider2D* other)
	{
	}
	void SCRIPT_Gate::OnCollisionStay(Collider2D* other)
	{
	}
	void SCRIPT_Gate::OnCollisionExit(Collider2D* other)
	{
	}
}