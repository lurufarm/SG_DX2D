#include "Item_Selected.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "SCENE_PlayScene.h"
#include "Img_LevUP2.h"
#include "SCRIPT_Item.h"


namespace sg
{
	Item_Selected::Item_Selected()
	{
		PlayScene* ps = dynamic_cast<PlayScene*>(SceneManager::GetActiveScene());
		if (ps)
			mID = ps->SelectedItemID;
		else
			mID = 0;
		Item_Selected::Initialize();
	}
	Item_Selected::~Item_Selected()
	{
	}
	void Item_Selected::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		SetMesh();

		switch (mID)
		{
		case 0: // 보너스 라이프 mLife
			SetMaterial(L"BonusLife");
			break;
		case 1: // 흡혈 ++ mHPStealRatio
			SetMaterial(L"StealHP");
			break;
		case 2: // 질긴 생명 ++ mHPHealRatio
			SetMaterial(L"HealHP");
			break;
		case 3: // 공격력 증가 mStrength
			SetMaterial(L"EStrength");
			break;
		case 4: // 방어력 증가 mDefence
			SetMaterial(L"EDefence");
			break;
		case 5: // 공격 범위 증가 mRange
			SetMaterial(L"ERange");
			break;
		case 6: // 공격 지속 시간 증가 mAttackDuration
			SetMaterial(L"EAduration");
			break;
		case 7: // 공격 횟수 증가 (멀티샷) mAttackCount
			SetMaterial(L"EAcount");
			break;
		case 8: // 발사체 수 증가 mProjectiles
			SetMaterial(L"Eprojs");
			break;
		case 9: // 공격 속도 증가 mAttackSpeed
			SetMaterial(L"EAspeed");
			break;
		case 10: // 이동 속도 증가 mSpeed
			SetMaterial(L"Espeed");
			break;
		case 11: // 최대 체력 증가 mMaxHP
			SetMaterial(L"EmaxHP");
			break;
		case 20: // cheese선택
			SetMaterial(L"Item_Cheeseicon");
			break;
		case 21: // cheese선택
			SetMaterial(L"Item_Lucyicon");
			break;
		case 22: // cheese선택
			SetMaterial(L"Item_Roboicon");
			break;
		}
		mMr->Initialize();

		AddComp<SCRIPT_Item>();
	}
	void Item_Selected::Update()
	{
		PlayScene* ps = dynamic_cast<PlayScene*>(SceneManager::GetActiveScene());
		if (ps)
			mID = ps->SelectedItemID;
		else
			mID = 0;

		switch (mID)
		{
		case 0: // 보너스 라이프 mLife
			SetMaterial(L"BonusLife");
			break;
		case 1: // 흡혈 ++ mHPStealRatio
			SetMaterial(L"StealHP");
			break;
		case 2: // 질긴 생명 ++ mHPHealRatio
			SetMaterial(L"HealHP");
			break;
		case 3: // 공격력 증가 mStrength
			SetMaterial(L"EStrength");
			break;
		case 4: // 방어력 증가 mDefence
			SetMaterial(L"EDefence");
			break;
		case 5: // 공격 범위 증가 mRange
			SetMaterial(L"ERange");
			break;
		case 6: // 공격 지속 시간 증가 mAttackDuration
			SetMaterial(L"EAduration");
			break;
		case 7: // 공격 횟수 증가 (멀티샷) mAttackCount
			SetMaterial(L"EAcount");
			break;
		case 8: // 발사체 수 증가 mProjectiles
			SetMaterial(L"Eprojs");
			break;
		case 9: // 공격 속도 증가 mAttackSpeed
			SetMaterial(L"EAspeed");
			break;
		case 10: // 이동 속도 증가 mSpeed
			SetMaterial(L"Espeed");
			break;
		case 11: // 최대 체력 증가 mMaxHP
			SetMaterial(L"EmaxHP");
			break;
		case 20: // cheese선택
			SetMaterial(L"Item_Cheeseicon");
			break;
		case 21: // cheese선택
			SetMaterial(L"Item_Lucyicon");
			break;
		case 22: // cheese선택
			SetMaterial(L"Item_Roboicon");
			break;
		}

		if (mGetFirstPos == false)
		{
			mPos = mTr->GetPosition();
			mGetFirstPos = true;
		}

		mTime += Time::DeltaTime();
		Vector3 pos = mTr->GetPosition();
		float range = 5.0;
		float omega = 3.0f;
		float offset = mPos.y;

		pos.y = offset + range * sin(omega * mTime);

		mTr->SetPosition(pos);

		Gobj_Item::Update();
	}
	void Item_Selected::LateUpdate()
	{
		Gobj_Item::LateUpdate();
	}
	void Item_Selected::Render()
	{
		Gobj_Item::Render();
	}

}