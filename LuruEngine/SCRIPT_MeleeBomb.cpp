#include "SCRIPT_MeleeBomb.h"
#include "..\Engine_SOURCE\sgTime.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgCollider2D.h"
#include "..\Engine_SOURCE\sgAnimator.h"
#include "Gobj_Monster.h"
#include "Effect_MobExplosion.h"

namespace sg
{
	void SCRIPT_MeleeBomb::Attack()
	{
		mTime += Time::DeltaTime();

		Animator* at = mOwner->GetComp<Animator>();
		int Index = at->GetActiveAni()->GetAniIndex();
		std::wstring ownerName = mOwner->GetName();

		if (GetDistance() > mOwner->GetStat().mRange * 2.0f)
		{
			mFSMState = eFSMState::Move;
			at->PlayAnimation(AnimationName(move), false, mDirection);
		}

		Transform* tr = mOwner->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();

		float distance = GetDistance();
		float t = min(mTime / 2, 1.0f);
		float speed = sgLerp(mOwner->GetStat().mSpeed * 2, 10.0f, t);
		float distanceToMove = speed * Time::DeltaTime();
		Vector3 direction = GetDirection();
		direction.Normalize();
		pos += direction * distanceToMove;
		tr->SetPosition(pos);


		if (at->GetActiveAni()->GetKey() == AnimationName(attack)
			&& at->GetActiveAni()->IsComplete())
		{
			object::Instantiate<Effect_MobExplosion>(mOwner->GetComp<Transform>()->GetPosition(), eLayerType::Monster_Effect, SceneManager::GetActiveScene());
			mOwner->SetState(GameObject::eState::Dead);
		}

		if (mTime >= mOwner->GetStat().mCooldown && at->GetActiveAni()->GetKey() != AnimationName(attack))
		{
			at->PlayAnimation(AnimationName(attack), false, mDirection);
			mTime = 0.0f;
		}
	}
}