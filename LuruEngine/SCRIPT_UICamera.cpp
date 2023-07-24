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
		Transform* tr = GetOwner()->GetComp<Transform>(); // ī�޶��� Transform
		Transform* ptr = mPlayer->GetComp<Transform>(); // �÷��̾��� Transform

		Vector3 camerapos = tr->GetPosition(); // ī�޶��� ��ġ
		Vector3 playerpos = ptr->GetPosition(); // �÷��̾��� ��ġ

		Vector3 pos = camerapos + (playerpos - camerapos);

		tr->SetPosition(pos);
	}
}