#include "Img_CharIcon.h"
#include "SCRIPT_UI.h"

namespace sg
{
	Img_CharIcon::Img_CharIcon(int num)
	{
		mIconNum = num;
		Img_CharIcon::Initialize();
	}
	Img_CharIcon::~Img_CharIcon()
	{
	}
	void Img_CharIcon::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();

		if (mSelected)
		{
			switch (mIconNum)
			{
			case 0:
				SetMaterial(L"UICheeseicon");
				break;
			case 1:
				SetMaterial(L"UILucyicon");
				break;
			case 2:
				SetMaterial(L"UIRoboicon");
				break;
			case 3:
				SetMaterial(L"UISzilaicon");
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

		mMr->Initialize();

	}
	void Img_CharIcon::Update()
	{
		if (mSelected)
		{
			switch (mIconNum)
			{
			case 0:
				SetMaterial(L"UICheeseicon");
				break;
			case 1:
				SetMaterial(L"UILucyicon");
				break;
			case 2:
				SetMaterial(L"UIRoboicon");
				break;
			case 3:
				SetMaterial(L"UISzilaicon");
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