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

		if (Input::KeyP(eKeyCode::W))
		{
			pos.y += 300 * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::KeyP(eKeyCode::S))
		{
			pos.y -= 300 * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::KeyP(eKeyCode::A))
		{
			pos.x -= 300 * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::KeyP(eKeyCode::D))
		{
			pos.x += 300 * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::KeyP(eKeyCode::Q))
		{
			pos.z -= 300 * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::KeyP(eKeyCode::E))
		{
			pos.z += 300 * Time::DeltaTime();
			tr->SetPosition(pos);
		}
	}
}