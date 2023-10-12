#include "SCRIPT_CameraScript.h"
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgTime.h"
#include "..\Engine_SOURCE\sgInput.h"

namespace sg
{
	void SCRIPT_CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();

		if (Input::KeyP(eKeyCode::UP))
		{
			pos.y += 150 * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::KeyP(eKeyCode::DOWN))
		{
			pos.y -= 150 * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::KeyP(eKeyCode::LEFT))
		{
			pos.x -= 150 * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::KeyP(eKeyCode::RIGHT))
		{
			pos.x += 150 * Time::DeltaTime();
			tr->SetPosition(pos);
		}
	}
}