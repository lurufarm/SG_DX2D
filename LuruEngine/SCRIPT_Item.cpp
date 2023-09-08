#include "SCRIPT_Item.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgGameObject.h"
#include "Gobj_Player.h"
#include "Img_LevUp2.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	SCRIPT_Item::SCRIPT_Item()
	{
	}
	SCRIPT_Item::~SCRIPT_Item()
	{
	}
	void SCRIPT_Item::Initialize()
	{
		mOwner = dynamic_cast<Item_Selected*>(GetOwner());
		mPlayer = Player;
	}
	void SCRIPT_Item::Update()
	{
	}
	void SCRIPT_Item::OnCollisionEnter(Collider2D* other)
	{
		if (other == mPlayer->GetComp<Collider2D>())
		{
			switch (mOwner->GetItemID())
			{
			case 0: // 보너스 라이프 mLife
				mPlayer->BonusLife();
				break;
			case 1: // 흡혈 ++ mHPStealRatio
				mPlayer->EnhenceHPStealRatio();
				break;
			case 2: // 질긴 생명 ++ mHPHealRatio
				mPlayer->EnhenceHPHealRatio();
				break;
			case 3: // 공격력 증가 mStrength
				mPlayer->EnhenceStrength();
				break;
			case 4: // 방어력 증가 mDefence
				mPlayer->EnhenceDefence();
				break;
			case 5: // 공격 범위 증가 mRange
				mPlayer->EnhenceRange();
				break;
			case 6: // 공격 지속 시간 증가 mAttackDuration
				mPlayer->EnhenceAttackDuration();
				break;
			case 7: // 공격 횟수 증가 (멀티샷) mAttackCount
				mPlayer->EnhenceAttackCount();
				break;
			case 8: // 발사체 수 증가 mProjectilesa
				mPlayer->EnhenceProjectileCount();
				break;
			case 9: // 공격 속도 증가 mAttackSpeed
				mPlayer->EnhenceAttackSpeed();
				break;
			case 10: // 이동 속도 증가 mSpeed
				mPlayer->EnhenceSpeed();
				break;
			case 11: // 최대 체력 증가 mMaxHP
				mPlayer->EnhenceMaxHP();
				break;
			}
			object::Instantiate<Img_LevUP2>(eLayerType::Effect, SceneManager::GetActiveScene());
			mOwner->SetState(GameObject::eState::Dead);
		}
	}
}