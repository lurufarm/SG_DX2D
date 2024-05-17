#include "SCRIPT_CharInfo.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "Gobj_Font.h"
#include "Gobj_Player.h"
#include "Gobj_Character.h"
#include <string>

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
			mOwner->SetFontOption(pos.x, pos.y, 15.0f, FONT_RGBA(255, 255, 255, 255));
			
			std::wstring text;
			text += L"공격력		";
			text += std::to_wstring(mChar->GetStat().mStrength);
			text += L"\n방어력		";
			text += std::to_wstring(mChar->GetStat().mDefence);
			text += L"\n이동속도		";
			text += std::to_wstring(mChar->GetStat().mSpeed);
			text += L"\n공격속도		";
			text += std::to_wstring(mChar->GetStat().mAttackSpeed);


			mOwner->SetText(text.c_str());
		}
		else
			mOwner->SetText(L"");
		
	}
}