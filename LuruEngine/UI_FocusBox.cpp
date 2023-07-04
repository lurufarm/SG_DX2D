#include "UI_FocusBox.h"
#include "sgTime.h"

namespace sg
{
	UI_FocusBox::UI_FocusBox(int num)
	{
		mNum = num;

		std::wstring name = Gobj_UI::GetName();
		name += L"_FocusBox";
		SetName(name);

		UI_FocusBox::Initialize();

	}
	UI_FocusBox::~UI_FocusBox()
	{
	}
	void UI_FocusBox::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		switch (mNum)
		{
		case 0:
			SetMaterial(L"UISBox_tl");
			break;
		case 1:
			SetMaterial(L"UISBox_tr");
			break;
		case 2:
			SetMaterial(L"UISBox_bl");
			break;
		case 3:
			SetMaterial(L"UISBox_br");
			break;
		}

		mMr->Initialize();

		Gobj_UI::Initialize();
	}
	void UI_FocusBox::Update()
	{

		//float moverange = 0.2f;
		//float frequency = 0.1f;
		//float x = this->GetComp<Transform>()->GetPosition().x + moverange * sin(frequency * Time::DeltaTime());
		//float y = this->GetComp<Transform>()->GetPosition().y + moverange * cos(frequency * Time::DeltaTime());

		//mTr->SetPosition(Vector3(x, y, -2.0f));

		Gobj_UI::Update();
	}
	void UI_FocusBox::LateUpdate()
	{
		Gobj_UI::LateUpdate();
	}
	void UI_FocusBox::Render()
	{
		Gobj_UI::Render();
	}
}