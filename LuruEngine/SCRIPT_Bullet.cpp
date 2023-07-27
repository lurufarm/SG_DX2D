#include "SCRIPT_Bullet.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "Gobj_Character.h"
#include "Gobj_Player.h"
#include "Effect_Hit.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	void SCRIPT_Bullet::Initialize()
	{
		mTime = 0.0f;
		mBullet = (Gobj_Bullet*)GetOwner();
		mBulletType = mBullet->GetBulletType();
		Transform* tr = mBullet->GetComp<Transform>();
		IsLaunched = false;
		Vector2 distance = Vector2(mBullet->GetTargetPos().x - mBullet->GetFirstPos().x, mBullet->GetTargetPos().y - mBullet->GetFirstPos().y);
		mTotalDuration = distance.Length() / 100.0f;

		mPlayer = Player;
		mBulletOwner = mBullet->GetBulletOwner();

		Vector3 direction = mBullet->GetTargetPos() - mBullet->GetFirstPos();
		direction.Normalize();
		float angleRad = std::acos(direction.x); // acos() �Լ��� ����Ͽ� x����� ������ ���մϴ�.
		if (direction.y < 0) // ���� ������ y���� ������ ������ ������ ��ȯ�մϴ�.
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
		Vector3 curPos;
		if (mBulletType == eBulletType::Basic)
		{
			curPos = mBullet->GetFirstPos() + t * (mBullet->GetTargetPos() - mBullet->GetFirstPos());
			curPos.z = -1.0f;
			mBullet->GetComp<Transform>()->SetPosition(curPos);
		}

		if (mBulletType == eBulletType::Curved)
		{
			float curveHeight = 20.0f; // ��� ����
			float curveDuration = mTotalDuration * 2.0f; // � � �ð�

			Vector3 targetPos = mBullet->GetTargetPos();
			Vector3 startPos = mBullet->GetFirstPos();

			// �ð��� ��ȭ���� ���
			float deltaTime = Time::DeltaTime();
			float t = mTime / curveDuration;
			mTime += deltaTime;

			// ������ ��� �������� x, y, z ��ǥ ���
			float xDist = targetPos.x - startPos.x; // x ��ǥ�� �̵� �Ÿ�
			float yDist = targetPos.y - startPos.y; // y ��ǥ�� �̵� �Ÿ�
			float x = startPos.x + t * xDist;
			float y = startPos.y + t * yDist + curveHeight * 4.0f * t * (1.0f - t);

			float z = -1.0f; // Assuming the z-position remains constant

			curPos = Vector3(x, y, z);
			mBullet->GetComp<Transform>()->SetPosition(curPos);

			// ��� ������ �Ѿ��� �����ϰų� ��Ȱ��ȭ ó�� ���� ����
			if (t >= 1.0f)
			{
				mBullet->SetState(GameObject::eState::Dead);
			}
		}


		// Bullet State Changing
			Vector2 distance = Vector2(curPos.x - mBullet->GetFirstPos().x, curPos.y - mBullet->GetFirstPos().y);
			float dislength = distance.Length();
		if (dislength >= mPlayer->GetChar()->GetStat().mRange)
		{
			mBullet->SetState(GameObject::eState::Dead);
		}
	}
	void SCRIPT_Bullet::OnCollisionEnter(Collider2D* other)
	{
		Vector3 pos = other->GetOwner()->GetComp<Transform>()->GetPosition();
		object::Instantiate<Effect_Hit>(pos, eLayerType::Effect, SceneManager::GetActiveScene());
		GetOwner()->SetState(GameObject::eState::Dead);
	}
	void SCRIPT_Bullet::OnCollisionStay(Collider2D* other)
	{
	}
	void SCRIPT_Bullet::OnCollisionExit(Collider2D* other)
	{
	}
}