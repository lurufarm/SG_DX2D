#include "SCRIPT_Tile1.h"

#include "..\Engine_SOURCE\sgGameObject.h"

#include "Gobj_Player.h"

namespace sg
{
	void SCRIPT_Tile1::Initialize()
	{
	}
	void SCRIPT_Tile1::Update()
	{
		mTr = GetOwner()->GetComp<Transform>();
		mCol = GetOwner()->GetComp<Collider2D>();
	}
	void SCRIPT_Tile1::LateUpdate()
	{
	}
	void SCRIPT_Tile1::Render()
	{
	}
	void SCRIPT_Tile1::OnCollisionEnter(Collider2D* other)
	{
		other->GetOwner()->SetTransParent(true);
	}
	void SCRIPT_Tile1::OnCollisionStay(Collider2D* other)
	{
	}
	void SCRIPT_Tile1::OnCollisionExit(Collider2D* other)
	{
		other->GetOwner()->SetTransParent(false);
	}
}