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
	}
	void SCRIPT_Gate::Update()
	{
		mItem = mOwner->GetItem();

		if (mOwner->GetIsOpen())
		{
			mItem->SetState(GameObject::eState::Active);
			Vector3 ppos = Player->GetComp<Transform>()->GetPosition();
			Vector3 opos = mOwner->GetComp<Transform>()->GetPosition();
			float distance = Vector2(ppos.x - opos.x, ppos.y - opos.y).Length();

			if (mOwner->GetSelected() && distance <= 80.0f)
			{
				if (mTextBG == nullptr)
				{
					mTextBG = object::Instantiate<UI_TextBG>(2, eLayerType::UI, mOwner->GetMyScene());
					mTextBG->Initialize();
				}
				mTextBG->SetState(GameObject::eState::Active);
				int itemID = mItem->GetItemID();
				switch (itemID)
				{
				case 0:
					mTextBG->SetTextBGSize(3.0f);
					wcscpy_s(FontWrapper::mText, L"추가 생명");
					break;
				case 1 :
					mTextBG->SetTextBGSize(2.0f);
					wcscpy_s(FontWrapper::mText, L"흡혈");
					break;
				case 2:
					mTextBG->SetTextBGSize(3.0f);
					wcscpy_s(FontWrapper::mText, L"질긴 생명");
					break;
				case 3:
					mTextBG->SetTextBGSize(3.0f);
					wcscpy_s(FontWrapper::mText, L"공격력 증가");
					break;
				case 4:
					mTextBG->SetTextBGSize(2.0f);
					wcscpy_s(FontWrapper::mText, L"방어력 증가");
					break;
				case 5:
					mTextBG->SetTextBGSize(3.0f);
					wcscpy_s(FontWrapper::mText, L"공격 범위 증가");
					break;
				case 6:
					mTextBG->SetTextBGSize(5.0f);
					wcscpy_s(FontWrapper::mText, L"공격 지속시간 증가");
					break;
				case 7:
					mTextBG->SetTextBGSize(2.0f);
					wcscpy_s(FontWrapper::mText, L"멀티 샷");
					break;
				case 8:
					mTextBG->SetTextBGSize(5.0f);
					wcscpy_s(FontWrapper::mText, L"발사체 갯수 증가");
					break;
				case 9:
					mTextBG->SetTextBGSize(4.0f);
					wcscpy_s(FontWrapper::mText, L"공격 속도 증가");
					break;
				case 10:
					mTextBG->SetTextBGSize(4.0f);
					wcscpy_s(FontWrapper::mText, L"이동 속도 증가");
					break;
				case 11:
					mTextBG->SetTextBGSize(4.0f);
					wcscpy_s(FontWrapper::mText, L"최대 체력 증가");
					break;
				case 20:
					mTextBG->SetTextBGSize(2.0f);
					wcscpy_s(FontWrapper::mText, L"치즈");
					break;
				case 21:
					mTextBG->SetTextBGSize(2.0f);
					wcscpy_s(FontWrapper::mText, L"루시");
					break;
				case 22:
					mTextBG->SetTextBGSize(2.0f);
					wcscpy_s(FontWrapper::mText, L"로보");
					break;
				case 23:
					mTextBG->SetTextBGSize(2.0f);
					wcscpy_s(FontWrapper::mText, L"실라");
					break;
				}

				Vector3 fontPos = mTextBG->GetTextBGL()->GetComp<Transform>()->GetPosition();
				fontPos.x += 3.0f;
				fontPos.y += 5.0f;
				fontPos = WorldPosToScreen(fontPos);
				FontWrapper::SetFontOption(fontPos.x, fontPos.y, 25.0f, FONT_RGBA(255, 255, 255, 255));
			}
			else
			{
				if (mTextBG)
					mTextBG->SetState(GameObject::eState::Paused);
					//wcscpy_s(FontWrapper::mText, L"");
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
				wcscpy_s(FontWrapper::mText, L"");
			}
		}
		else
		{
			if (mTextBG)
				mTextBG->SetState(GameObject::eState::Paused);
			wcscpy_s(FontWrapper::mText, L"");
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