#include "Img_TextBG_middle.h"
#include "SCRIPT_TextBG.h"

namespace sg
{
	Img_TextBG_middle::Img_TextBG_middle(float size)
	{
		SetName(L"TextBG_middle");
		mTr = GetComp<Transform>();
		mTr->SetScale(size, 1.0, 1.0f);

		Img_TextBG_middle::Initialize();
	}
	Img_TextBG_middle::~Img_TextBG_middle()
	{
	}
	void Img_TextBG_middle::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		SetMaterial(L"ImgTextBGmiddle");
		mMr->Initialize();


	}
	void Img_TextBG_middle::Update()
	{
		Gobj_Img::Update();
	}
	void Img_TextBG_middle::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_TextBG_middle::Render()
	{
		Gobj_Img::Render();
	}
}