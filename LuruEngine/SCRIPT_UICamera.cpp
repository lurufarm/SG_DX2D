#include "SCRIPT_UICamera.h"
#include "sgRenderer.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	void SCRIPT_UICamera::Initialize()
	{
		mPlayer = Player;
	}
	void SCRIPT_UICamera::Update()
	{
		Transform* tr = GetOwner()->GetComp<Transform>(); // 카메라의 Transform
		Transform* ptr = mPlayer->GetComp<Transform>(); // 플레이어의 Transform

		Vector3 camerapos = tr->GetPosition(); // 카메라의 위치
		Vector3 playerpos = ptr->GetPosition(); // 플레이어의 위치

		Vector3 pos = camerapos + (playerpos - camerapos);

		tr->SetPosition(pos);
	}
}