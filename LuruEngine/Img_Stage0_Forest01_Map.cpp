#include "Img_Stage0_Forest01_Map.h"

namespace sg
{
	Img_Stage0_Map::Img_Stage0_Map(Stage0 num)
	{
		SetName(L"Img_Stage0_Forest01_Map");

		mNum = num;

		Img_Stage0_Map::Initialize();
	}
	Img_Stage0_Map::~Img_Stage0_Map()
	{
	}
	void Img_Stage0_Map::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		switch (mNum)
		{
		case sg::Img_Stage0_Map::Stage0::forestfd01:
			SetMaterial(L"Stage0ForestFd01_Map");
			break;
		case sg::Img_Stage0_Map::Stage0::forestfd02:
			SetMaterial(L"Stage0ForestFd02_Map");
			break;
		case sg::Img_Stage0_Map::Stage0::forestfd03:
			SetMaterial(L"Stage0ForestFd03_Map");
			break;
		case sg::Img_Stage0_Map::Stage0::forestfd04:
			SetMaterial(L"Stage0ForestFd04_Map");
			break;
		case sg::Img_Stage0_Map::Stage0::forestdg01:
			SetMaterial(L"Stage0ForestDg01_Map");
			break;
		case sg::Img_Stage0_Map::Stage0::forestdg02:
			SetMaterial(L"Stage0ForestDg02_Map");
			break;
		case sg::Img_Stage0_Map::Stage0::forestdg03:
			SetMaterial(L"Stage0ForestDg03_Map");
			break;
		case sg::Img_Stage0_Map::Stage0::forestdg04:
			SetMaterial(L"Stage0ForestDg04_Map");
			break;
		}

		mMr->Initialize();

		Gobj_Img::Initialize();
	}
	void Img_Stage0_Map::Update()
	{
		Gobj_Img::Update();
	}
	void Img_Stage0_Map::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_Stage0_Map::Render()
	{
		Gobj_Img::Render();
	}
}