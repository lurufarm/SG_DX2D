#include "sgGameObject.h"
#include "sgRenderer.h"
#include "sgGraphicDevice_Dx11.h"
#include "sgInput.h"

namespace sg
{
	GameObject::GameObject()
		: mState(eState::Active)
	{
	}
	GameObject::~GameObject()
	{
	}
	void GameObject::Initialize()
	{
	}
	void GameObject::Update()
	{
	}
	void GameObject::LateUpdate()
	{
	}
	void GameObject::Render()
	{
	}
}