#include "SCRIPT_MobProjectile.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "Gobj_Character.h"
#include "Gobj_Player.h"
#include "Effect_Hit.h"
#include "Effect_Explosion.h"
#include "Effect_FirePlate.h"
#include "Effect_ProjectileDest.h"
#include "Effect_RockDust.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	void SCRIPT_MobProjectile::Initialize()
	{
		mTime = 0.0f;
		mProj = (Gobj_MobProjectile*)GetOwner();
		mProjOwner = mProj->GetProjOwner();
		mProjType = mProj->GetProjType();
		mTarget = Player;
		mFirstPos = mProjOwner->GetComp<Transform>()->GetPosition();
		mLastPos = mTarget->GetComp<Transform>()->GetPosition();

		mTotalDuration = GetDistance() / 200.0f;
		IsLaunched = false;

	}
	void SCRIPT_MobProjectile::Update()
	{
		mTime += Time::DeltaTime();
		float t = mTime / mTotalDuration;
		Vector3 curPos;
		Vector2 curDir = GetDirection();
		float speed = mProjOwner->GetStat().mSpeed * mTotalDuration * 10.0f;
		if (mProjType == eMProjType::PoisonOrb)
		{
			// Set the amplitude of the sine wave
			float amplitude = 5.0f;
			// Set the frequency of the sine wave
			float frequency = 15.0f;

			// Calculate the new position
			curPos.x = mFirstPos.x + curDir.x * t * speed;
			curPos.y = mFirstPos.y + curDir.y * t * speed + sin(t * frequency) * amplitude;
			curPos.z = -1.0f;
			mProj->GetComp<Transform>()->SetPosition(curPos);
		}
		else if (mProjType == eMProjType::EntRock)
		{
			float curveHeight = 30.0f; // 곡선의 높이
			float curveDuration = 1.0f; // 곡선 운동 시간

			// 시간의 변화량을 계산
			float t = mTime / curveDuration;

			// 포물선 곡선을 따르도록 x, y, z 좌표 계산
			float xDist = mLastPos.x - mFirstPos.x; // x 좌표의 이동 거리
			float yDist = mLastPos.y - mFirstPos.y; // y 좌표의 이동 거리
			float x = mFirstPos.x + t * xDist;
			float y = mFirstPos.y + t * yDist + curveHeight * 4.0f * t * (1.0f - t);
			float z = -1.0f;
			curPos = Vector3(x, y, z);
			mProj->GetComp<Transform>()->SetPosition(curPos);
		}



		// Bullet State Changing : 사정거리 이상이 되면 사라진다
		if (GetDistance() >= mProjOwner->GetStat().mRange * 2.0f)
		{
			mProj->SetState(GameObject::eState::Dead);
		}
	}
	void SCRIPT_MobProjectile::OnCollisionEnter(Collider2D* other)
	{

		if (mProjOwner->GetName() == L"Ent")
		{
			mProj->SetState(GameObject::eState::Dead);
			object::Instantiate<Effect_RockDust>(Vector3(mLastPos.x, mLastPos.y + 10.0f, mLastPos.z), eLayerType::Effect, SceneManager::GetActiveScene());
		}
		else
		{
			Vector3 pos = other->GetOwner()->GetComp<Transform>()->GetPosition();
			object::Instantiate<Effect_Hit>(pos, eLayerType::Effect, SceneManager::GetActiveScene());
			mProj->SetState(GameObject::eState::Dead);
		}
	}
	void SCRIPT_MobProjectile::OnCollisionStay(Collider2D* other)
	{
	}
	void SCRIPT_MobProjectile::OnCollisionExit(Collider2D* other)
	{

	}
}