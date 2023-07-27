#include "SCRIPT_CharSelect.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgObject.h"

#include "UI_CharSelect.h"

namespace sg
{
	UI_CharSelect* SCRIPT_CharSelect::mObject = nullptr;
	SCRIPT_CharSelect::SCRIPT_CharSelect()
	{
	}
	SCRIPT_CharSelect::~SCRIPT_CharSelect()
	{
	}
	void SCRIPT_CharSelect::Initialize()
	{
		mOwner = (GameObject*)GetOwner();
	}
	void SCRIPT_CharSelect::Update()
	{
		if (Input::KeyD(eKeyCode::ENTER))
		{
			if (mOwner->GetSelected())
			{
				mObject = object::Instantiate<UI_CharSelect>(eLayerType::UI, SceneManager::GetActiveScene());
			}
		}
		if (Input::KeyD(eKeyCode::X))
		{
			if (mObject)
			{
				SceneManager::GetActiveScene()->DeleteGameObj(eLayerType::UI, mObject);
				delete mObject;
				mObject = nullptr;
			}
		}
	}
	void SCRIPT_CharSelect::OnCollisionEnter(Collider2D* other)
	{
	}
	void SCRIPT_CharSelect::OnCollisionStay(Collider2D* other)
	{
	}
	void SCRIPT_CharSelect::OnCollisionExit(Collider2D* other)
	{
	}
}