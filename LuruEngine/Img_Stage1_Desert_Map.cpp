#include "Img_Stage1_Desert_Map.h"

namespace sg
{
	Img_Stage1_Map::Img_Stage1_Map(Stage1 num)
	{
		SetName(L"Img_Stage1_Desert_Map");

		mNum = num;

		Img_Stage1_Map::Initialize();
	}
	Img_Stage1_Map::~Img_Stage1_Map()
	{
	}
	void Img_Stage1_Map::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		switch (mNum)
		{
		case sg::Img_Stage1_Map::Stage1::desert01:
			SetMaterial(L"Stage1Desert01_Map");
			break;
		case sg::Img_Stage1_Map::Stage1::desert02:
			SetMaterial(L"Stage1Desert02_Map");
			break;
		case sg::Img_Stage1_Map::Stage1::desert03:
			SetMaterial(L"Stage1Desert03_Map");
			break;
		case sg::Img_Stage1_Map::Stage1::desert04:
			SetMaterial(L"Stage1Desert04_Map");
			break;
		case sg::Img_Stage1_Map::Stage1::desertmidboss:
			SetMaterial(L"Stage1MidBoss_Map");
			break;
		}

		mMr->Initialize();

		Gobj_Img::Initialize();
	}
	void Img_Stage1_Map::Update()
	{
		Gobj_Img::Update();
	}
	void Img_Stage1_Map::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_Stage1_Map::Render()
	{
		Gobj_Img::Render();
	}
}