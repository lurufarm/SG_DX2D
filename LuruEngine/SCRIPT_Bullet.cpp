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
		Transform* tr = mOwner->GetComp<Transform>();
		IsLaunched = false;
		Vector2 distance = Vector2(mOwner->GetTargetPos().x - mOwner->GetFirstPos().x, mOwner->GetTargetPos().y - mOwner->GetFirstPos().y);
		mTotalDuration = distance.Length() / 100.0f;

		mPlayer = Player;

		Vector3 direction = mOwner->GetTargetPos() - mOwner->GetFirstPos();
		direction.Normalize();
		float angleRad = std::acos(direction.x); // acos() 함수를 사용하여 x축과의 각도를 구합니다.
		if (direction.y < 0) // 방향 벡터의 y값이 음수면 각도를 음수로 변환합니다.
		{
			angleRad = -angleRad;
		}
		float angleDegree = (angleRad * 180.0f / 3.1415926535f) - 90.0f;
		tr->SetRotation(Vector3(0.0f, 0.0f, angleDegree));



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