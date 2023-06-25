#include "Gobj_BGImg.h"

namespace sg
{
	Gobj_BGImg::Gobj_BGImg()
		: mLayer(eLayerType::BGImg)
	{
		SetName(L"Gobj_BGImg");
		AddComp<MeshRenderer>(); 
	}
	Gobj_BGImg::~Gobj_BGImg()
	{
	}
	void Gobj_BGImg::Initialize()
	{
		GameObject::Initialize(); // �̰� �������� �ƴұ��?
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
		GameObject::Render(); // �̰� �������� �ƴұ��?
	}
}