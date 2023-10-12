#include "Img_TextBG_left.h"
#include "SCRIPT_TextBG.h"

namespace sg
{
	Img_TextBG_left::Img_TextBG_left()
	{
		SetName(L"TextBG_left");
		Img_TextBG_left::Initialize();
	}
	Img_TextBG_left::~Img_TextBG_left()
	{
	}
	void Img_TextBG_left::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		SetMaterial(L"ImgTextBGleft");
		mMr->Initialize();


	}
	void Img_TextBG_left::Update()
	{
		Gobj_Img::Update();
	}
	void Img_TextBG_left::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_TextBG_left::Render()
	{
		Gobj_Img::Render();
	}
}