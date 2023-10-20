#include "SCRIPT_Bullet.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "Gobj_Character.h"
#include "Gobj_Player.h"
#include "Effect_Hit.h"
#include "Effect_Explosion.h"
#include "Effect_FirePlate.h"
#include "Effect_LaserHit.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	void SCRIPT_Bullet::Initialize()
	{

		mTime = 0.0f;
		mBullet = (Gobj_Bullet*)GetOwner();
		mBulletType = mBullet->GetBulletType();
		IsLaunched = false;
		mPlayer = Player;
		mBulletOwner = mBullet->GetBulletOwner();

		mTotalProjs = mBulletOwner->GetStat().mProjectileCount;
		mThisNum = mBullet->GetThisNum();
		mFirstPos = mBullet->GetFirstPos();
		mCurPos = mFirstPos;
		GetLastPos(mThisNum);
		mTotalDuration = GetDistance() / 100.0f;

		if (mBulletType == eBulletType::Cheese)
		{
			Vector2 direction = GetDirection();
			float angleDegree = sgGetAngle(direction) - 90.0f;
			Transform* tr = mBullet->GetComp<Transform>();
			tr->SetRotation(Vector3(0.0f, 0.0f, angleDegree));
		}
		else if (mBulletType == eBulletType::Robo)
		{
			if (mPlayer->GetTarget())
				mLastPos = mPlayer->GetTarget()->GetComp<Transform>()->GetPosition();
			if (mBulletOwner->GetTarget())
				mLastPos = mBulletOwner->GetTarget()->GetComp<Transform>()->GetPosition();
			Vector2 direction = GetDirection();
			float angleDegree = sgGetAngle(direction) - 90.0f;
			float angleRadian = sgGetAngleInRadian(angleDegree + 90.0f);
			Vector2 pos = GetBeamPos(160.0f, angleRadian);
			Vector3 lastpos = Vector3(pos.x, pos.y, -1.0f);
			Transform* tr = mBullet->GetComp<Transform>();
			tr->SetRotation(Vector3(0.0f, 0.0f, angleDegree));
			tr->SetPosition(lastpos);
		}
		else if (mBulletType == eBulletType::Szila)
		{
			Vector3 dir = mLastPos - mFirstPos;
			dir.z = 0.0f;
			dir.Normalize();
			float angle = sgGetAngle(Vector2(dir.x, dir.y));
			float angle2 = angle;
			angle = sgGetAngleInRadian(angle + 90.0f);
			angle2 = sgGetAngleInRadian(angle2);
			Collider2D* col = mBullet->GetComp<Collider2D>();
			col->SetSize(Vector2(30.0f, 100.0f));
			Vector2 pos2d = sgGetBeamPos(col->GetCSize().y / 2, angle2, Vector2(mFirstPos.x, mFirstPos.y));
			pos2d.x -= mFirstPos.x;
			pos2d.y -= mFirstPos.y;
			col->SetCenter(pos2d);
			mBullet->GetComp<Transform>()->SetRotation(0.0f, 0.0f, angle);

		}
	}
	void SCRIPT_Bullet::Update()
	{
		mTime += Time::DeltaTime();
		if (mBulletType == eBulletType::Cheese)
		{
			Vector3 Direction = mLastPos - mFirstPos;
			Direction.Normalize();
			mCurPos += mPlayer->GetStat().mAttackSpeed * Time::DeltaTime() * Direction;
			mCurPos.z = -1.0f;
			mBullet->GetComp<Transform>()->SetPosition(mCurPos);

			Vector2 distance = Vector2(mCurPos.x - mBullet->GetFirstPos().x, mCurPos.y - mBullet->GetFirstPos().y);
			float dislength = distance.Length();
			if (dislength >= mPlayer->GetChar()->GetStat().mRange * 1.5f)
			{
				mBullet->SetState(GameObject::eState::Dead);
			}
		}

		if (mBulletType == eBulletType::Lucy) // �������� �׸��� Projectile
		{
			float curveHeight = 20.0f; // ��� ����
			//float curveDuration = mTotalDuration * 0.7; // � � �ð�
			float curveDuration = mTotalDuration * (mBulletOwner->GetStat().mAttackSpeed / 100.0f); // � � �ð�

			// �ð��� ��ȭ���� ���
			float t = mTime / curveDuration;

			// ������ ��� �������� x, y, z ��ǥ ���
			float xDist = mLastPos.x - mFirstPos.x; // x ��ǥ�� �̵� �Ÿ�
			float yDist = mLastPos.y - mFirstPos.y; // y ��ǥ�� �̵� �Ÿ�
			float x = mFirstPos.x + t * xDist;
			float y = mFirstPos.y + t * yDist + curveHeight * 4.0f * t * (1.0f - t);
			float z = -1.0f;

			mCurPos = Vector3(x, y, z);
			mBullet->GetComp<Transform>()->SetPosition(mCurPos);

			// �ƹ��� ���� �ʾƵ� �����ϸ� ����
			if (t >= 1.0f)
			{
				object::Instantiate<Effect_FirePlate>(mCurPos, eLayerType::Effect, SceneManager::GetActiveScene());
				object::Instantiate<Effect_Explosion>(mCurPos, eLayerType::Effect, SceneManager::GetActiveScene());
				mBullet->SetState(GameObject::eState::Dead);
			}
		}
		if (mBulletType == eBulletType::Szila)
		{
			if (mTime >= 2.0f)
				mBullet->SetState(GameObject::eState::Dead);
		}

		 //��� Bullet�� �����Ÿ� �̻��� �Ǹ� �������.

	}
	void SCRIPT_Bullet::OnCollisionEnter(Collider2D* other)
	{
		Vector3 pos = other->GetOwner()->GetComp<Transform>()->GetPosition();
		
		if (dynamic_cast<Gobj_Monster*>(other->GetOwner()))
			mPlayer->HPSteal();

		if (mBullet->GetBulletType() == eBulletType::Lucy)
		{
			object::Instantiate<Effect_FirePlate>(Vector3(pos.x, pos.y, pos.z + 0.01f), eLayerType::Effect, SceneManager::GetActiveScene());
			object::Instantiate<Effect_Explosion>(pos, eLayerType::Effect, SceneManager::GetActiveScene());
		}
		else if (mBulletType == eBulletType::Robo)
			object::Instantiate<Effect_LaserHit>(Vector3(pos.x, pos.y, pos.z - 1.0f), eLayerType::Player_Effect, SceneManager::GetActiveScene());

		if (mBulletType != eBulletType::Robo && mBulletType != eBulletType::Szila)
		{
			object::Instantiate<Effect_Hit>(pos, eLayerType::Effect, SceneManager::GetActiveScene());
			GetOwner()->SetState(GameObject::eState::Dead);
		}

	}
	void SCRIPT_Bullet::OnCollisionStay(Collider2D* other)
	{
	}
	void SCRIPT_Bullet::OnCollisionExit(Collider2D* other)
	{

	}
	void SCRIPT_Bullet::GetLastPos(int n)
	{
		mLastPos = mBullet->GetLastPos();

		if (n >= 2)
		{
			if (n % 2 == 0)
			{
				float angledegree = 10.0f * n;
				float angle = angledegree * (3.141592 / 180.0f);
				Vector2 direction = GetDirection();
				mLastPos.x = cos(angle) * direction.x - sin(angle) * direction.y;
				mLastPos.y = sin(angle) * direction.x + cos(angle) * direction.y;
				mLastPos += mFirstPos;
			}
			else
			{
				float angledegree = -10.0f * (n - 1.0f);
				float angle = angledegree * (3.141592 / 180.0f);
				Vector2 direction = GetDirection();
				mLastPos.x = cos(angle) * direction.x - sin(angle) * direction.y;
				mLastPos.y = sin(angle) * direction.x + cos(angle) * direction.y;
				mLastPos += mFirstPos;
			}
		}
	}
}