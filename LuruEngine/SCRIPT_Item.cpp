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
				for (Gobj_Character* company : mPlayer->GetActiveCompanies())
				{
					company->EnhenceStrength();
				}
				break;
			case 4: // ���� ���� mDefence
				mPlayer->EnhenceDefence();
				break;
			case 5: // ���� ���� ���� mRange
				mPlayer->EnhenceRange();
				for (Gobj_Character* company : mPlayer->GetActiveCompanies())
				{
					company->EnhenceRange();
				}
				break;
			case 6: // ���� ���� �ð� ���� mAttackDuration
				mPlayer->EnhenceAttackDuration();
				for (Gobj_Character* company : mPlayer->GetActiveCompanies())
				{
					company->EnhenceAttackDuration();
				}
				break;
			case 7: // ���� Ƚ�� ���� (��Ƽ��) mAttackCount
				mPlayer->EnhenceAttackCount();
				for (Gobj_Character* company : mPlayer->GetActiveCompanies())
				{
					company->EnhenceAttackCount();
				}
				break;
			case 8: // �߻�ü �� ���� mProjectilesa
				mPlayer->EnhenceProjectileCount();
				for (Gobj_Character* company : mPlayer->GetActiveCompanies())
				{
					company->EnhenceProjectileCount();
				}
				break;
			case 9: // ���� �ӵ� ���� mAttackSpeed
				mPlayer->EnhenceAttackSpeed();
				for (Gobj_Character* company : mPlayer->GetActiveCompanies())
				{
					company->EnhenceAttackSpeed();
				}
				break;
			case 10: // �̵� �ӵ� ���� mSpeed
				mPlayer->EnhenceSpeed();
				for (Gobj_Character* company : mPlayer->GetActiveCompanies())
				{
					company->EnhenceSpeed();
				}
				break;
			case 11: // �ִ� ü�� ���� mMaxHP
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