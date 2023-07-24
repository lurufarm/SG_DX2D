#include "SCRIPT_MainCamera.h"
#include "sgRenderer.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	void SCRIPT_MainCamera::Initialize()
	{
		mPlayer = Player;
	}
	void SCRIPT_MainCamera::Update()
	{
		Transform* tr = GetOwner()->GetComp<Transform>(); // ī�޶��� Transform
		Transform* ptr = mPlayer->GetComp<Transform>(); // �÷��̾��� Transform

		Vector3 camerapos = tr->GetPosition(); // ī�޶��� ��ġ
		Vector3 playerpos = ptr->GetPosition(); // �÷��̾��� ��ġ

		float speed = 0.08f;
			
		Vector3 pos = camerapos + (playerpos - camerapos) * speed;

		tr->SetPosition(pos);
	}
}