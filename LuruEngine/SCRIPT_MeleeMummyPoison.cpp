#include "SCRIPT_MeleeMummyPoison.h"
#include "..\Engine_SOURCE\sgTime.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgCollider2D.h"
#include "..\Engine_SOURCE\sgAnimator.h"
#include "Gobj_Monster.h"
#include "Effect_MobExplosion.h"
#include "Bullet_PoisonOrb.h"

namespace sg
{
	void SCRIPT_MeleeMummyPoison::Attack()
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
		float speed = sgLerp(mOwner->GetStat().mSpeed, 10.0f, t);
		float distanceToMove = speed * Time::DeltaTime();
		Vector3 direction = GetDirection();
		direction.Normalize();
		pos += direction * distanceToMove;
		tr->SetPosition(pos);

		if (at->GetActiveAni()->GetKey() == AnimationName(attack)
			&& at->GetActiveAni()->IsComplete())
		{
			Vector3 ownerPos = tr->GetPosition();
			Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
			Vector3 down = Vector3(0.0f, -1.0f, 0.0f);
			Vector3 left = Vector3(-1.0f, 0.0f, 0.0f);
			Vector3 right = Vector3(1.0f, 0.0f, 0.0f);
			object::Instantiate<Effect_MobExplosion>(mOwner->GetComp<Transform>()->GetPosition(), eLayerType::Monster_Effect, SceneManager::GetActiveScene());
			object::PoisonOrb(mOwner, up);
			object::PoisonOrb(mOwner, down);
			object::PoisonOrb(mOwner, left);
			object::PoisonOrb(mOwner, right);
			mOwner->SetState(GameObject::eState::Dead);
		}

		if (mTime >= mOwner->GetStat().mCooldown && at->GetActiveAni()->GetKey() != AnimationName(attack))
		{
			at->PlayAnimation(AnimationName(attack), false, mDirection);
			mTime = 0.0f;
		}
	}
}