#include "Gobj_BGImg.h"

namespace sg
{
	Gobj_BGImg::Gobj_BGImg()
		: mLayer(eLayerType::BGImg)
	{
		SetName(L"Gobj_BGImg");
		AddComp<MeshRenderer>(); 
		// 여기에 셋메쉬를 넣는건 어땠을지
	}
	Gobj_BGImg::~Gobj_BGImg()
	{
	}
	void Gobj_BGImg::Initialize()
	{
		GameObject::Initialize(); // 이거 빼먹은거 아닐까요?
	}
	void Gobj_BGImg::Update()
	{
		GameObject::Update();
	}
	void Gobj_BGImg::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Gobj_BGImg::Render()
	{
		GameObject::Render(); // 이거 빼먹은거 아닐까요?
	}
}