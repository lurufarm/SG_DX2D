#include "sgCameraScript.h"
#include "sgGameObject.h"
#include "sgTransform.h"
#include "sgTime.h"
#include "sgInput.h"

namespace sg
{
	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();

		if (Input::KeyP(eKeyCode::W))
		{
			pos.y += 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::KeyP(eKeyCode::S))
		{
			pos.y -= 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::KeyP(eKeyCode::A))
		{
			pos.x -= 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::KeyP(eKeyCode::D))
		{
			pos.x += 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::KeyP(eKeyCode::Q))
		{
			pos.z -= 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::KeyP(eKeyCode::E))
		{
			pos.z += 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
	}
}