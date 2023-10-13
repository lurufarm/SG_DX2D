#include "Img_BulletIcon.h"

namespace sg
{
	Img_BulletIcon::Img_BulletIcon(int num)
	{
		mIconNum = num;
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
			SetMaterial(L"UI_Cheesebullet");
			break;
		case 1:
			SetMaterial(L"UI_Lucybullet");
			break;
		case 2:
			SetMaterial(L"UI_Robobeam");
			break;
		case 3:
			SetMaterial(L"UI_Szilafire");
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