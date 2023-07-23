#include "SCRIPT_Bullet.h"
#include "Gobj_Character.h"
#include "Gobj_Player.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	void SCRIPT_Bullet::Initialize()
	{
		mTime = 0.0f;
		mOwner = (Gobj_Bullet*)GetOwner();
		IsLaunched = false;
		Vector2 distance = Vector2(mOwner->GetTargetPos().x - mOwner->GetFirstPos().x, mOwner->GetTargetPos().y - mOwner->GetFirstPos().y);
		mTotalDuration = distance.Length() / 100.0f;

		mPlayer = Player;

	}
	void SCRIPT_Bullet::Update()
	{
		mTime += Time::DeltaTime();
		float t = mTime / mTotalDuration;
		Vector3 curPos = mOwner->GetFirstPos() + t * (mOwner->GetTargetPos() - mOwner->GetFirstPos());
		curPos.z = -1.0f;
		mOwner->GetComp<Transform>()->SetPosition(curPos);
		Vector2 distance = Vector2(curPos.x - mOwner->GetFirstPos().x, curPos.y - mOwner->GetFirstPos().y);
		float dislength = distance.Length();

		if (dislength >= mPlayer->GetChar()->GetStat().mRange)
		{
			mOwner->SetState(GameObject::eState::Dead);
		}

	}
	void SCRIPT_Bullet::OnCollisionEnter(Collider2D* other)
	{
	}
	void SCRIPT_Bullet::OnCollisionStay(Collider2D* other)
	{
	}
	void SCRIPT_Bullet::OnCollisionExit(Collider2D* other)
	{
	}
}