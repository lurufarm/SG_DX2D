#include "SCRIPT_Gate.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "..\Engine_SOURCE\sgFontWrapper.h"
#include "SCENE_PlayScene.h"
#include "SCENE_PlayScene2.h"
#include "Interact_Gate.h"
#include "Item_AbilityEnhancer.h"
#include "Gobj_Item.h"
#include "UI_TextBG.h"
#include "Img_TextBG_left.h"
#include "Gobj_Font.h"
#include "Gobj_Player.h"

extern sg::Gobj_Player* Player;

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
		mText = object::Instantiate<Gobj_Font>(eLayerType::UI, mOwner->GetMyScene());
		mTextBG = object::Instantiate<UI_TextBG>(2, eLayerType::UI, mOwner->GetMyScene());
		mTextBG->SetState(GameObject::eState::Paused);
		mTextBG->Initialize();
	}
	void SCRIPT_Gate::Update()
	{
		mItem = mOwner->GetItem();
		Vector3 fontPos = mTextBG->GetTextBGL()->GetComp<Transform>()->GetPosition();
		fontPos.x += 3.0f;
		fontPos.y += 5.0f;
		fontPos = WorldPosToScreen(fontPos);
		mText->SetFontOption(fontPos.x, fontPos.y, 25.0f, FONT_RGBA(255, 255, 255, 255));

		if (mOwner->GetIsOpen())
		{
			mItem->SetState(GameObject::eState::Active);
			Vector3 ppos = Player->GetComp<Transform>()->GetPosition();
			Vector3 opos = mOwner->GetComp<Transform>()->GetPosition();
			float distance = Vector2(ppos.x - opos.x, ppos.y - opos.y).Length();

			if (mOwner->GetSelected() && distance <= 60.0f)
			{
				mTextBG->SetState(GameObject::eState::Active);
				mText->SetState(GameObject::eState::Active);
				int itemID = mItem->GetItemID();
				switch (itemID)
				{
				case 0:
					mTextBG->SetTextBGSize(3.0f);
					mText->SetText(L"�߰� ����");
					break;
				case 1 :
					mTextBG->SetTextBGSize(2.0f);
					mText->SetText(L"����");
					break;
				case 2:
					mTextBG->SetTextBGSize(3.0f);
					mText->SetText(L"���� ����");
					break;
				case 3:
					mTextBG->SetTextBGSize(3.0f);
					mText->SetText(L"���ݷ� ����");
					break;
				case 4:
					mTextBG->SetTextBGSize(2.0f);
					mText->SetText(L"���� ����");
					break;
				case 5:
					mTextBG->SetTextBGSize(3.0f);
					mText->SetText(L"���� ���� ����");
					break;
				case 6:
					mTextBG->SetTextBGSize(5.0f);
					mText->SetText(L"���� ���ӽð� ����");
					break;
				case 7:
					mTextBG->SetTextBGSize(2.0f);
					mText->SetText(L"��Ƽ ��");
					break;
				case 8:
					mTextBG->SetTextBGSize(5.0f);
					mText->SetText(L"�߻�ü ���� ����");
					break;
				case 9:
					mTextBG->SetTextBGSize(4.0f);
					mText->SetText(L"���� �ӵ� ����");
					break;
				case 10:
					mTextBG->SetTextBGSize(4.0f);
					mText->SetText(L"�̵� �ӵ� ����");
					break;
				case 11:
					mTextBG->SetTextBGSize(4.0f);
					mText->SetText(L"�ִ� ü�� ����");
					break;
				case 20:
					mTextBG->SetTextBGSize(1.5f);
					mText->SetText(L"ġ��");
					break;
				case 21:
					mTextBG->SetTextBGSize(1.5f);
					mText->SetText(L"���");
					break;
				case 22:
					mTextBG->SetTextBGSize(1.5f);
					mText->SetText(L"�κ�");
					break;
				case 23:
					mTextBG->SetTextBGSize(1.5f);
					mText->SetText(L"�Ƕ�");
					break;
				}

			}
			else
			{
				mTextBG->SetState(GameObject::eState::Paused);
				mText->SetText(L"");
				mText->SetState(GameObject::eState::Paused);
			}

			if (mOwner->GetSelected() && Input::KeyD(eKeyCode::N))
			{
				Scene* sc = SceneManager::LoadNextScene();
				PlayScene* ps = dynamic_cast<PlayScene*>(sc);
				PlayScene2* ps2 = dynamic_cast<PlayScene2*>(sc);
				if (ps != nullptr)
				{
					ps->SelectedItemID = mItem->GetItemID();
				}

				if (ps2 != nullptr)
				{
					ps2->SelectedItemID = mItem->GetItemID();
				}
				mItem->SetItemActivate(true);
				mText->SetText(L"");
				mText->SetState(GameObject::eState::Paused);
			}
		}
		else
		{
			mTextBG->SetState(GameObject::eState::Paused);
			mText->SetText(L"");
			mText->SetState(GameObject::eState::Paused);
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