#include "UI_Icons.h"

namespace sg
{
	UI_Icons::UI_Icons(int num)
	{
		
		std::wstring name = Gobj_UI::GetName();
		name += L"_Icons";
		name += num;

		mNum = num;

		SetName(name);
		
		UI_Icons::Initialize();
	}
	UI_Icons::~UI_Icons()
	{
	}
	void UI_Icons::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		
		switch (mNum)
		{
		case 0: // ����
			SetMaterial(L"UICoin");
			mTr->SetPosition(180, 100, -1.0f);
			break;
		case 1: // �ɼ�
			SetMaterial(L"UIOption");
			mTr->SetPosition(-180, 100, -1.0f);
			break;
		case 2: // �䳢������
			SetMaterial(L"UITokki");
			mTr->SetPosition(-180, -100, -1.0f);
			break;
		case 3: // �䳢 �� J
			SetMaterial(L"UIJbutton");
			mTr->SetPosition(-165, -100, -1.0f);
			break;
		case 4: // �÷���������
			SetMaterial(L"UIPlus");
			mTr->SetPosition(180, -100, -1.0f);
			break;
		case 5: // �÷��� �� K
			SetMaterial(L"UIKbutton");
			mTr->SetPosition(165, -100, -1.0f);
			break;

		default:
			break;
		}

		mMr->Initialize();
		
	}
	void UI_Icons::Update()
	{
		Gobj_UI::Update();
	}
	void UI_Icons::LateUpdate()
	{
		Gobj_UI::LateUpdate();
	}
	void UI_Icons::Render()
	{
		Gobj_UI::Render();
	}
}