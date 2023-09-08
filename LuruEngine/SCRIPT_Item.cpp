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
			case 0: // ���ʽ� ������ mLife
				mPlayer->BonusLife();
				break;
			case 1: // ���� ++ mHPStealRatio
				mPlayer->EnhenceHPStealRatio();
				break;
			case 2: // ���� ���� ++ mHPHealRatio
				mPlayer->EnhenceHPHealRatio();
				break;
			case 3: // ���ݷ� ���� mStrength
				mPlayer->EnhenceStrength();
				break;
			case 4: // ���� ���� mDefence
				mPlayer->EnhenceDefence();
				break;
			case 5: // ���� ���� ���� mRange
				mPlayer->EnhenceRange();
				break;
			case 6: // ���� ���� �ð� ���� mAttackDuration
				mPlayer->EnhenceAttackDuration();
				break;
			case 7: // ���� Ƚ�� ���� (��Ƽ��) mAttackCount
				mPlayer->EnhenceAttackCount();
				break;
			case 8: // �߻�ü �� ���� mProjectilesa
				mPlayer->EnhenceProjectileCount();
				break;
			case 9: // ���� �ӵ� ���� mAttackSpeed
				mPlayer->EnhenceAttackSpeed();
				break;
			case 10: // �̵� �ӵ� ���� mSpeed
				mPlayer->EnhenceSpeed();
				break;
			case 11: // �ִ� ü�� ���� mMaxHP
				mPlayer->EnhenceMaxHP();
				break;
			}
			object::Instantiate<Img_LevUP2>(eLayerType::Effect, SceneManager::GetActiveScene());
			mOwner->SetState(GameObject::eState::Dead);
		}
	}
}