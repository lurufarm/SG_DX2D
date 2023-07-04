#include "UI_FocusBoxes.h"

namespace sg
{
	UI_FocusBoxes::UI_FocusBoxes()
	{
		SetName(L"Gobj_FocusBoxes");

		UI_FocusBoxes::Initialize();
	}
	UI_FocusBoxes::~UI_FocusBoxes()
	{
	}
	void UI_FocusBoxes::Initialize()
	{
		mFirst = new UI_FocusBox(0);
		mSecond = new UI_FocusBox(1);
		mThird = new UI_FocusBox(2);
		mFourth = new UI_FocusBox(3);


		GameObject::Initialize();
	}
	void UI_FocusBoxes::Update()
	{
		GameObject::Update();
	}
	void UI_FocusBoxes::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void UI_FocusBoxes::Render()
	{
		GameObject::Render();
	}
	void UI_FocusBoxes::SetSelectObj(GameObject* obj)
	{
		mObj = obj;

		Vector3 objpos = obj->GetComp<Transform>()->GetPosition();
		Vector3 objscale = obj->GetComp<MeshRenderer>()->GetImgScale();

		mFirst->GetComp<Transform>()->SetPosition(Vector3(objpos.x - objscale.x * 0.5f - 0.2f, objpos.y + objscale.y * 0.5f + 0.2f, -2.0f));
		mSecond->GetComp<Transform>()->SetPosition(Vector3(objpos.x + objscale.x * 0.5f + 0.2f, objpos.y + objscale.y * 0.5f + 0.2f, -2.0f));
		mThird->GetComp<Transform>()->SetPosition(Vector3(objpos.x - objscale.x * 0.5f - 0.2f, objpos.y - objscale.y * 0.5f - 0.2f, -2.0f));
		mFourth->GetComp<Transform>()->SetPosition(Vector3(objpos.x + objscale.x * 0.5f + 0.2f, objpos.y - objscale.y * 0.5f - 0.2f, -2.0f));

	}
}