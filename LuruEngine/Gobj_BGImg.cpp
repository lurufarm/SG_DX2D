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
		GameObject::Initialize(); // ¿Ã∞≈ ª©∏‘¿∫∞≈ æ∆¥“±Óø‰?
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
		GameObject::Render(); // ¿Ã∞≈ ª©∏‘¿∫∞≈ æ∆¥“±Óø‰?
	}
}