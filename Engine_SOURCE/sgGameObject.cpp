#include "sgGameObject.h"
#include "sgRenderer.h"
#include "sgGraphicDevice_Dx11.h"
#include "sgTransform.h"

namespace sg
{
	GameObject::GameObject()
		: mState(eState::Active)
	{
		AddComp<Transform>();
	}
	GameObject::~GameObject()
	{
	}
	void GameObject::Initialize()
	{
	}
	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			comp->Update();
		}
	}
	void GameObject::LateUpdate()
	{
		for (Component* comp : mComponents)
		{
			comp->LateUpdate();
		}
	}
	void GameObject::Render()
	{
		for (Component* comp : mComponents)
		{
			comp->Render();
		}
	}
}