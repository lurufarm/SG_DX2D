#include "Img_SelectText.h"

namespace sg
{
	Img_SelectText::Img_SelectText(bool type)
	{
		std::wstring name = Gobj_Img::GetName();
		
		if (type)
		{
			name += L"_SelectText_Stoty";
		}
		else
		{
			name += L"_SelectText_Party";
		}

		mType = type;
		SetName(name);

		Img_SelectText::Initialize();
	}
	Img_SelectText::~Img_SelectText()
	{
	}
	void Img_SelectText::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();

		if (mType)
		{
			SetMaterial(L"ImgStory_text");
			mTr->SetPosition(Vector3(-58.5, 58.5, -0.1f));
		}
		else
		{
			SetMaterial(L"ImgParty_text");
			mTr->SetPosition(Vector3(58.5, 58.5, -0.1f));

		}
		
		mMr->Initialize();

		Gobj_Img::Initialize();
	}
	void Img_SelectText::Update()
	{
		Gobj_Img::Update();
	}
	void Img_SelectText::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_SelectText::Render()
	{
		Gobj_Img::Render();
	}
}