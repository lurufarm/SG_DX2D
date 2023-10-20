#include "SCRIPT_CharInfo.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "Gobj_Font.h"
#include "Gobj_Player.h"
#include "Gobj_Character.h"

namespace sg
{
	SCRIPT_CharInfo::SCRIPT_CharInfo(int num)
	{
		if (num == 0)
			mChar = SceneManager::GetChar(L"Cheese");
		else if (num == 1)
			mChar = SceneManager::GetChar(L"Lucy");
		else if (num == 2)
			mChar = SceneManager::GetChar(L"Robo");
		else if (num == 3)
			mChar = SceneManager::GetChar(L"Szila");
	}
	void SCRIPT_CharInfo::Initialize()
	{
		mOwner = (Gobj_Font*)GetOwner();
	}
	void SCRIPT_CharInfo::Update()
	{
		if (mOwner->GetState() == GameObject::eState::Active)
		{
			Vector3 pos = mOwner->GetComp<Transform>()->GetPosition();
			pos = WorldPosToScreen(pos);
			mOwner->SetFontOption(pos.x, pos.y, 20.0f, FONT_RGBA(255, 255, 255, 255));

			//std::wstring text = (L"공격력			");
			//text += mChar->GetStat().mStrength;
			//mOwner->SetText(text.s);
			mOwner->SetText(L"공격력		test\n이동속도		test\n공격속도		test\n발사체 수		test\n");
		}
		else
			mOwner->SetText(L"");
		
	}
}