#include "SCRIPT_UI.h"
#include "Gobj_Player.h"

extern sg::Gobj_Player* Player;

void sg::SCRIPT_UI::Initialize()
{
	mPlayer = Player;
	Transform* tr = GetOwner()->GetComp<Transform>();
	mOwnerPos = tr->GetPosition();
}

void sg::SCRIPT_UI::Update()
{
	Transform* ptr = mPlayer->GetComp<Transform>();

	GetOwner()->GetComp<Transform>()->SetPosition(ptr->GetPosition() + mOwnerPos);

}
