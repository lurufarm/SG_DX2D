#include "Img_Finish.h"
#include "SCRIPT_UI.h"
#include "Gobj_Player.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	Img_Finish::Img_Finish()
	{
		SetName(L"FinishLight");
		Img_Finish::Initialize();
	}
	Img_Finish::~Img_Finish()
	{
	}
	void Img_Finish::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		SetMaterial(L"ImgSunLight");
		mMr->Initialize();
		//Vector3 ppos = Player->GetComp<Transform>()->GetPosition();
		Vector3 mypos = Vector3(-120.0f, 70.0f, 0.0f);
		mTr->SetPosition(mypos);
		AddComp<SCRIPT_UI>();
		Light* mLight = AddComp<Light>();
		mLight->SetType(eLightType::Point);
		mLight->SetColor(Vector4(0.8f, 0.8f, 0.5f, 0.3f));
		mLight->SetRadius(200.0f);
		mLight->SetLightPos(Vector3(-96.0f, 64.0f, 0.0f));
	}
	void Img_Finish::Update()
	{
		Gobj_Img::Update();
	}
	void Img_Finish::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_Finish::Render()
	{
		Gobj_Img::Render();
	}
}