#include "SCRIPT_Gate.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "SCENE_PlayScene.h"
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

			if (mOwner->GetSelected() && Input::KeyD(eKeyCode::N))
			{
				Scene* sc = SceneManager::LoadNextScene();
				PlayScene* ps = dynamic_cast<PlayScene*>(sc);
				ps->SelectedItemID = mItem->GetItemID();
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