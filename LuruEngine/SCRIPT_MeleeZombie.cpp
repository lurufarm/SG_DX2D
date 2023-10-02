#include "SCRIPT_MeleeZombie.h"
#include "..\Engine_SOURCE\sgTime.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgAnimator.h"
#include "Gobj_Monster.h"
#include "Effect_MobExplosion.h"
#include "Monsters.h"

namespace sg
{
	void SCRIPT_MeleeZombie::Move()
	{
		if (mOwner2 == nullptr)
			mOwner2 = dynamic_cast<Melee_Zombie*>(mOwner);

		mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(move), true, mDirection);

		Transform* tr = mOwner->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();

		float distance = GetDistance();
		float distanceToMove = 0.0f;
		if (distance <= mOwner->GetStat().mRange * 1.5f)
		{
			distanceToMove = mOwner->GetStat().mSpeed * 2.5f * Time::DeltaTime();
			mOwner2->mMSpeed = 0.02f;
		}
		else
		{
			distanceToMove = mOwner->GetStat().mSpeed * Time::DeltaTime();
			mOwner2->mMSpeed = 0.15f;
		}
		
		Vector3 direction = GetDirection();
		direction.Normalize();
		pos += direction * distanceToMove;
		tr->SetPosition(pos);

		if (distance <= mOwner->GetStat().mRange)
			mFSMState = eFSMState::Attack;
	}
}