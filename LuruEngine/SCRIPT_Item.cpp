#include "SCRIPT_Item.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgGameObject.h"
#include "SCENE_PlayScene.h"
#include "SCENE_PlayScene2.h"
#include "Gobj_Player.h"
#include "Img_LevUp2.h"
#include "SCRIPT_Company.h"
#include "UI_StatusBase.h"

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
		Gobj_Character* cheese = SceneManager::GetChar(L"Cheese");
		Gobj_Character* lucy = SceneManager::GetChar(L"Lucy");
		Gobj_Character* robo = SceneManager::GetChar(L"Robo");
		Gobj_Character* szila = SceneManager::GetChar(L"Szila");


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
				for (Gobj_Character* company : mPlayer->GetActiveCompanies())
				{
					company->EnhenceStrength();
				}
				break;
			case 4: // 방어력 증가 mDefence
				mPlayer->EnhenceDefence();
				break;
			case 5: // 공격 범위 증가 mRange
				mPlayer->EnhenceRange();
				for (Gobj_Character* company : mPlayer->GetActiveCompanies())
				{
					company->EnhenceRange();
				}
				break;
			case 6: // 공격 지속 시간 증가 mAttackDuration
				mPlayer->EnhenceAttackDuration();
				for (Gobj_Character* company : mPlayer->GetActiveCompanies())
				{
					company->EnhenceAttackDuration();
				}
				break;
			case 7: // 공격 횟수 증가 (멀티샷) mAttackCount
				mPlayer->EnhenceAttackCount();
				for (Gobj_Character* company : mPlayer->GetActiveCompanies())
				{
					company->EnhenceAttackCount();
				}
				break;
			case 8: // 발사체 수 증가 mProjectilesa
				mPlayer->EnhenceProjectileCount();
				for (Gobj_Character* company : mPlayer->GetActiveCompanies())
				{
					company->EnhenceProjectileCount();
				}
				break;
			case 9: // 공격 속도 증가 mAttackSpeed
				mPlayer->EnhenceAttackSpeed();
				for (Gobj_Character* company : mPlayer->GetActiveCompanies())
				{
					company->EnhenceAttackSpeed();
				}
				break;
			case 10: // 이동 속도 증가 mSpeed
				mPlayer->EnhenceSpeed();
				for (Gobj_Character* company : mPlayer->GetActiveCompanies())
				{
					company->EnhenceSpeed();
				}
				break;
			case 11: // 최대 체력 증가 mMaxHP
				mPlayer->EnhenceMaxHP();
				break;
			case 20:
				if (mPlayer->GetChar() == cheese)
					mPlayer->EXP(150);
				else
				{
					if (cheese->GetComp<SCRIPT_Company>())
						cheese->EXP(150);
					else
					{
						cheese->AddComp<SCRIPT_Company>();
						if (GetOwner()->GetMyScene() == dynamic_cast<PlayScene*>(GetOwner()->GetMyScene()))
						{
							SceneManager::GetStatusBase()->MakeStatusSheet(cheese);
							SceneManager::GetStatusBase()->StateUpdate();
						}
					}
				}
				break;
			case 21:
				if (mPlayer->GetChar() == lucy)
					mPlayer->EXP(150);
				else
				{
					if (lucy->GetComp<SCRIPT_Company>())
						lucy->EXP(150);
					else
						lucy->AddComp<SCRIPT_Company>();
					if (GetOwner()->GetMyScene() == dynamic_cast<PlayScene*>(GetOwner()->GetMyScene()))
					{
						SceneManager::GetStatusBase()->MakeStatusSheet(lucy);
						SceneManager::GetStatusBase()->StateUpdate();
					}

				}
				break;
			case 22:
				if (mPlayer->GetChar() == robo)
					mPlayer->EXP(150);
				else
				{
					if (robo->GetComp<SCRIPT_Company>())
						robo->EXP(150);
					else
						robo->AddComp<SCRIPT_Company>();
					if (GetOwner()->GetMyScene() == dynamic_cast<PlayScene*>(GetOwner()->GetMyScene()))
					{
						SceneManager::GetStatusBase()->MakeStatusSheet(robo);
						SceneManager::GetStatusBase()->StateUpdate();
					}

				}
				break;
			case 23:
				if (mPlayer->GetChar() == szila)
					mPlayer->EXP(150);
				else
				{
					if (robo->GetComp<SCRIPT_Company>())
						robo->EXP(150);
					else
						robo->AddComp<SCRIPT_Company>();
					if (GetOwner()->GetMyScene() == dynamic_cast<PlayScene*>(GetOwner()->GetMyScene()))
					{
						SceneManager::GetStatusBase()->MakeStatusSheet(szila);
						SceneManager::GetStatusBase()->StateUpdate();
					}

				}
				break;
			}

			object::Instantiate<Img_LevUP2>(eLayerType::Effect, SceneManager::GetActiveScene());
			mOwner->SetState(GameObject::eState::Dead);
		}
	}
}