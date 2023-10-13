#include "Img_CharIcon.h"

namespace sg
{
	Img_CharIcon::Img_CharIcon(int num)
	{
		mIconNum = num;
	}
	Img_CharIcon::~Img_CharIcon()
	{
	}
	void Img_CharIcon::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();

		switch (mIconNum)
		{
		case 0:
			SetMaterial(L"Item_Cheeseicon");
			break;
		case 1:
			SetMaterial(L"Item_Lucyicon");
			break;
		case 2:
			SetMaterial(L"Item_Roboicon");
			break;
		case 3:
			SetMaterial(L"Item_Szilaicon");
			break;
		}

		mMr->Initialize();

	}
	void Img_CharIcon::Update()
	{
		if (mSelected)
		{
			switch (mIconNum)
			{
			case 0:
				SetMaterial(L"UI_Cheeseicon");
				break;
			case 1:
				SetMaterial(L"UI_Lucyicon");
				break;
			case 2:
				SetMaterial(L"UI_Roboicon");
				break;
			case 3:
				SetMaterial(L"UI_Szilaicon");
				break;
			}
		}
		else
		{
			switch (mIconNum)
			{
			case 0:
				SetMaterial(L"Item_Cheeseicon");
				break;
			case 1:
				SetMaterial(L"Item_Lucyicon");
				break;
			case 2:
				SetMaterial(L"Item_Roboicon");
				break;
			case 3:
				SetMaterial(L"Item_Szilaicon");
				break;
			}
		}
		Gobj_Img::Update();
	}
	void Img_CharIcon::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_CharIcon::Render()
	{
		Gobj_Img::Render();
	}
}