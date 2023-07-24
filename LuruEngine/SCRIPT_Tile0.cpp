#include "SCRIPT_Tile0.h"
#include "..\Engine_SOURCE\sgGameObject.h"

namespace sg
{
	void SCRIPT_Tile0::Initialize()
	{
	}
	void SCRIPT_Tile0::Update()
	{
		mTr = GetOwner()->GetComp<Transform>();
		mCol = GetOwner()->GetComp<Collider2D>();
	}
	void SCRIPT_Tile0::LateUpdate()
	{
	}
	void SCRIPT_Tile0::Render()
	{
	}
	void SCRIPT_Tile0::OnCollisionEnter(Collider2D* other)
	{
		mTr = GetOwner()->GetComp<Transform>();

		Vector3 otherpos = other->GetOwner()->GetComp<Transform>()->GetPosition();
		Vector3 mypos = mTr->GetPosition();
		if (otherpos.x <= mypos.x)
			otherpos.x--;
		else if (otherpos.x > mypos.x)
			otherpos.x++;
		if (otherpos.y <= mypos.y)
			otherpos.y--;
		else if (otherpos.y > mypos.y)
			otherpos.y++;

		other->GetOwner()->GetComp<Transform>()->SetPosition(otherpos);
	}
	void SCRIPT_Tile0::OnCollisionStay(Collider2D* other)
	{
		Vector3 otherpos = other->GetOwner()->GetComp<Transform>()->GetPosition();
		Vector3 mypos = mTr->GetPosition();
		if (otherpos.x < mypos.x)
			otherpos.x++;
		else if (otherpos.x > mypos.x)
			otherpos.x--;
		if (otherpos.y < mypos.y)
			otherpos.y--;
		else if (otherpos.y > mypos.y)
			otherpos.y++;

		other->GetOwner()->GetComp<Transform>()->SetPosition(otherpos);
	}
	void SCRIPT_Tile0::OnCollisionExit(Collider2D* other)
	{
	}
}