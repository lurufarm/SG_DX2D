#include "Gobj_Effect.h"

namespace sg
{
	Gobj_Effect::Gobj_Effect()
	{
		GetComp<Transform>();
		AddComp<MeshRenderer>();
		AddComp<Animator>();
	}
	Gobj_Effect::~Gobj_Effect()
	{
	}
	void Gobj_Effect::Initialize()
	{
	}
	void Gobj_Effect::Update()
	{
		GameObject::Update();
	}
	void Gobj_Effect::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Gobj_Effect::Render()
	{
		GameObject::Render();
	}
}