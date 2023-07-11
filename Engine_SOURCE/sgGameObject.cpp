#include "sgGameObject.h"
#include "sgRenderer.h"
#include "sgGraphicDevice_Dx11.h"
#include "sgTransform.h"

namespace sg
{
	GameObject::GameObject()
		: mState(eState::Active)
		, mOrder(0)
	{
		AddComp<Transform>();
	}
	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			delete comp;
			comp = nullptr;
		}

		for (Script* script:mScripts)
		{
			if (script == nullptr)
				continue;
			
			delete script;
			script = nullptr;
		}
	}
	void GameObject::Initialize()
	{
		//for (Component* comp : mComponents)
		//{
		//	comp->Initialize();        // Å×½ºÆ®
		//}
	}
	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			comp->Update();
		}

		for (Script* script : mScripts)
		{
			script->Update();
		}
	}
	void GameObject::LateUpdate()
	{
		for (Component* comp : mComponents)
		{
			comp->LateUpdate();
		}

		for (Script* script : mScripts)
		{
			script->LateUpdate();
		}
	}
	void GameObject::Render()
	{
		for (Component* comp : mComponents)
		{
			comp->Render();
		}

		for (Script* script : mScripts)
		{
			script->Render();
		}
	}
}