#include "SCRIPT_WormEggs.h"
#include "..\Engine_SOURCE\sgTime.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgCollider2D.h"
#include "..\Engine_SOURCE\sgAnimator.h"
#include "Gobj_Monster.h"
#include "Effect_MobExplosion.h"
#include "Melee_Scarab.h"

namespace sg
{
	void SCRIPT_WormEggs::Update()
	{
		if (mOwner->GetStat().mCurHP <= 0)
			mFSMState = eFSMState::Death;
		if (mTarget == nullptr || mTarget->GetState() == GameObject::eState::Dead)
			mFSMState = eFSMState::Idle;

		switch (mFSMState)
		{
		case sg::SCRIPT_MeleeMob::eFSMState::Spwan:
			Spawn();
			break;
		case sg::SCRIPT_MeleeMob::eFSMState::Idle:
			Idle();
			break;
		case sg::SCRIPT_MeleeMob::eFSMState::Move:
			Idle();
			break;
		case sg::SCRIPT_MeleeMob::eFSMState::Attack:
			Attack();
			break;
		case sg::SCRIPT_MeleeMob::eFSMState::Attacked:
			Attacked();
			break;
		case sg::SCRIPT_MeleeMob::eFSMState::Death:
			Death();
			break;
		}
	}
	void SCRIPT_WormEggs::Idle()
	{
		mTime += Time::DeltaTime();
		Animator* at = mOwner->GetComp<Animator>();
		at->PlayAnimation(AnimationName(idle), true, true);
		if (mTime >= 5.0f)
		{
			mSpawned = false;
			mTime = 0.0;
			mFSMState = eFSMState::Attack;
		}
	}
	void SCRIPT_WormEggs::Move()
	{
		mFSMState = eFSMState::Idle;
	}
	void SCRIPT_WormEggs::Attack()
	{
		Animator* at = mOwner->GetComp<Animator>();
		at->PlayAnimation(AnimationName(attack), true, true);
		int Index = at->GetActiveAni()->GetAniIndex();

		if (mSpawned || at->GetActiveAni()->IsComplete())
			mFSMState = eFSMState::Idle;

		if (mSpawned == false
			&& Index == 6
			&& at->GetActiveAni()->GetKey() == AnimationName(attack))
		{
			Vector3 pos = mOwner->GetComp<Transform>()->GetPosition();
			object::Instantiate<Melee_Scarab>(sgRandomPos(pos, 30.0f), eLayerType::Monster, SceneManager::GetActiveScene());
			mSpawned = true;
		}

	}
}