#include "Img_BulletIcon.h"
#include "SCRIPT_UI.h"

namespace sg
{
	Img_BulletIcon::Img_BulletIcon(int num)
	{
		mIconNum = num;
		Img_BulletIcon::Initialize();
	}
	Img_BulletIcon::~Img_BulletIcon()
	{
	}
	void Img_BulletIcon::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();

		switch (mIconNum)
		{
		case 0:
			SetMaterial(L"UICheesebullet");
			break;
		case 1:
			SetMaterial(L"UILucybullet");
			break;
		case 2:
			SetMaterial(L"UIRobobeam");
			break;
		case 3:
			SetMaterial(L"UISzilafire");
			break;
		}

		mMr->Initialize();
	}
	void Img_BulletIcon::Update()
	{
		Gobj_Img::Update();
	}
	void Img_BulletIcon::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_BulletIcon::Render()
	{
		Gobj_Img::Render();
	}
}