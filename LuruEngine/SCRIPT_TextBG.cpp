#include "SCRIPT_TextBG.h"
#include "Gobj_Player.h"
#include "UI_TextBG.h"
#include "Img_TextBG_left.h"
#include "Img_TextBG_middle.h"
#include "Img_TextBG_right.h"

extern sg::Gobj_Player* Player;

void sg::SCRIPT_TextBG::Initialize()
{
	mPlayer = Player;
	mOwner = (UI_TextBG*)GetOwner();

	mLeft = mOwner->GetTextBGL();
	mMiddle = mOwner->GetTextBGM();
	mRight = mOwner->GetTextBGR();



	mLeftPos = mLeft->GetComp<Transform>()->GetPosition();
	mMiddlePos = mMiddle->GetComp<Transform>()->GetPosition();
	mRightPos = mRight->GetComp<Transform>()->GetPosition();
	
}

void sg::SCRIPT_TextBG::Update()
{
	Transform* ptr = mPlayer->GetComp<Transform>();
	Vector3 ppos = ptr->GetPosition();

	float scaleratio = mOwner->GetTextBGSize();
	float xpos = scaleratio * 18.0f;
	mLeft->GetComp<Transform>()->SetPosition(-2.5f - xpos / 2.0f, 30.0f, 0.0f);
	mRight->GetComp<Transform>()->SetPosition(2.5f + xpos / 2.0f, 30.0f, 0.0f);
	mMiddle->GetComp<Transform>()->SetPosition(0.0f, 30.0f, 0.0f);

	mMiddle->GetComp<Transform>()->SetScale(xpos, 28.0f, 1.0f);

	mLeftPos = mLeft->GetComp<Transform>()->GetPosition();
	mMiddlePos = mMiddle->GetComp<Transform>()->GetPosition();
	mRightPos = mRight->GetComp<Transform>()->GetPosition();

	mLeft->GetComp<Transform>()->SetPosition(ppos + mLeftPos);
	mMiddle->GetComp<Transform>()->SetPosition(ppos + mMiddlePos);
	mRight->GetComp<Transform>()->SetPosition(ppos + mRightPos);


}
