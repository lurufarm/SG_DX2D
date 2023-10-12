#include "Img_TextBG_right.h"
#include "SCRIPT_TextBG.h"

namespace sg
{
	Img_TextBG_right::Img_TextBG_right()
	{
		SetName(L"TextBG_right");
		Img_TextBG_right::Initialize();
	}
	Img_TextBG_right::~Img_TextBG_right()
	{
	}
	void Img_TextBG_right::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		SetMaterial(L"ImgTextBGright");
		mMr->Initialize();

	}
	void Img_TextBG_right::Update()
	{
		Gobj_Img::Update();
	}
	void Img_TextBG_right::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_TextBG_right::Render()
	{
		Gobj_Img::Render();
	}
}