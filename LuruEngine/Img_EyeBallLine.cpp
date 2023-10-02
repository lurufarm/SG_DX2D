#include "Img_EyeBallLine.h"
#include "..\Engine_SOURCE\sgTime.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "Gobj_Player.h"
#include "Bullet_BloodSpit.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	Img_EyeBallLine::Img_EyeBallLine(Gobj_Monster* owner)
	{
		mOwner = owner;
		Img_EyeBallLine::Initialize();
	}
	Img_EyeBallLine::~Img_EyeBallLine()
	{
	}
	void Img_EyeBallLine::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();

		mTime = 0.0f;

		SetMesh();
		SetMaterial(L"ImgEyeBallLine");
	
		mTr->SetScale(Vector3(0.1f, 100.0f, 1.0f));
		mMr->Initialize();

		Vector3 ownerPos = mOwner->GetComp<Transform>()->GetPosition();
		ownerPos.y -= 5.0f;
		Vector3 targetPos = Player->GetComp<Transform>()->GetPosition();

		mDir = targetPos - ownerPos;
		mDir.z = 0.0f;
		mDir.Normalize();
		mAngle = sgGetAngle(Vector2(mDir.x, mDir.y));
		float angle2 = mAngle;
		mAngle = sgGetAngleInRadian(mAngle + 90.0f);
		angle2 = sgGetAngleInRadian(angle2);
		Vector2 pos2d = sgGetBeamPos(100.0f, angle2, Vector2(ownerPos.x, ownerPos.y));
		Vector3 pos3d = Vector3(pos2d.x, pos2d.y, -1.0f);
		mDir = pos3d;
		mDir.z = 0.0f;
		mTr->SetRotation(0.0f, 0.0f, mAngle);
		mTr->SetPosition(pos3d);
		
	}
	void Img_EyeBallLine::Update()
	{
		mTime += Time::DeltaTime();

		if (mTime >= 0.5f)
		{
			object::BloodSpit(mOwner, mDir);
			SetState(GameObject::eState::Dead);
		}
		Gobj_Img::Update();
	}
	void Img_EyeBallLine::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_EyeBallLine::Render()
	{
		Gobj_Img::Render();
	}
}