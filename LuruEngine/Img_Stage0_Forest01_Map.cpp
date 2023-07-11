#include "Img_Stage0_Forest01_Map.h"

namespace sg
{
	Img_Stage0_Forest01_Map::Img_Stage0_Forest01_Map(ForestFd num)
	{
		SetName(L"Img_Stage0_Forest01_Map");

		mNum = num;

		Img_Stage0_Forest01_Map::Initialize();
	}
	Img_Stage0_Forest01_Map::~Img_Stage0_Forest01_Map()
	{
	}
	void Img_Stage0_Forest01_Map::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		
		switch (mNum)
		{
		case sg::Img_Stage0_Forest01_Map::ForestFd::forest01:
			SetMaterial(L"Stage0ForestFd01_Map");
			break;
		case sg::Img_Stage0_Forest01_Map::ForestFd::forest02:
			break;
		case sg::Img_Stage0_Forest01_Map::ForestFd::forest03:
			break;
		case sg::Img_Stage0_Forest01_Map::ForestFd::forest04:
			break;
		case sg::Img_Stage0_Forest01_Map::ForestFd::forest05:
			break;
		case sg::Img_Stage0_Forest01_Map::ForestFd::forest06:
			break;
		case sg::Img_Stage0_Forest01_Map::ForestFd::end:
			break;
		default:
			break;
		}

		mMr->Initialize();

		Gobj_Img::Initialize();
	}
	void Img_Stage0_Forest01_Map::Update()
	{
		Gobj_Img::Update();
	}
	void Img_Stage0_Forest01_Map::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_Stage0_Forest01_Map::Render()
	{
		Gobj_Img::Render();
	}
}