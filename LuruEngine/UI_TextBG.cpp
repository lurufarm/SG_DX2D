#include "UI_TextBG.h"
#include "..\Engine_SOURCE\sgObject.h"

#include "Img_TextBG_left.h"
#include "Img_TextBG_middle.h"
#include "Img_TextBG_right.h"
#include "SCRIPT_TextBG.h"

namespace sg
{
	UI_TextBG::UI_TextBG(float size)
	{
		mSize = size;
	}
	UI_TextBG::~UI_TextBG()
	{
	}
	void UI_TextBG::Initialize()
	{
		Scene* mysc = GetMyScene();
		mTr = GetComp<Transform>();
		mLeft = object::Instantiate<Img_TextBG_left>(eLayerType::UI, GetMyScene());
		mMiddle = object::Instantiate<Img_TextBG_middle>(mSize, eLayerType::UI, GetMyScene());
		mRight = object::Instantiate<Img_TextBG_right>(eLayerType::UI, GetMyScene());

		AddComp<SCRIPT_TextBG>();
	}
	void UI_TextBG::Update()
	{
		mLeft->SetState(this->GetState());
		mMiddle->SetState(this->GetState());
		mRight->SetState(this->GetState());

		GameObject::Update();
	}
	void UI_TextBG::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void UI_TextBG::Render()
	{
		GameObject::Render();
	}
}