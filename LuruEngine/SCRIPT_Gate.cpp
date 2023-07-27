#include "SCRIPT_Gate.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgSceneManager.h"

namespace sg
{
	SCRIPT_Gate::SCRIPT_Gate()
	{
	}
	SCRIPT_Gate::~SCRIPT_Gate()
	{
	}
	void SCRIPT_Gate::Initialize()
	{
		mOwner = (GameObject*)GetOwner();
	}
	void SCRIPT_Gate::Update()
	{
		if (Input::KeyD(eKeyCode::ENTER))
		{
			if (mOwner->GetSelected())
			{
				SceneManager::LoadScene(L"Stage0_Forest01");
			}
		}
	}
	void SCRIPT_Gate::OnCollisionEnter(Collider2D* other)
	{
	}
	void SCRIPT_Gate::OnCollisionStay(Collider2D* other)
	{
	}
	void SCRIPT_Gate::OnCollisionExit(Collider2D* other)
	{
	}
}