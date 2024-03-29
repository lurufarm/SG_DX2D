#include "UI_FocusBoxes2.h"
#include <algorithm>
#include "..\Engine_SOURCE\sgTime.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgScene.h"
#include "..\Engine_SOURCE\sgObject.h"

#include "Gobj_Player.h"
#include "SCRIPT_Ui.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	UI_FocusBoxes2::UI_FocusBoxes2(Scene* myscene)
		: mObj(nullptr)
		, mObjs{}
		, mMyScene(myscene)
	{
		SetName(L"Gobj_FocusBoxes2");

		mObjs.clear();

		mBoxes[0] = object::Instantiate<UI_FocusBox>(0, eLayerType::UI, mMyScene);
		mBoxes[1] = object::Instantiate<UI_FocusBox>(1, eLayerType::UI, mMyScene);
		mBoxes[2] = object::Instantiate<UI_FocusBox>(2, eLayerType::UI, mMyScene);
		mBoxes[3] = object::Instantiate<UI_FocusBox>(3, eLayerType::UI, mMyScene);

		UI_FocusBoxes2::Initialize();
	}
	UI_FocusBoxes2::~UI_FocusBoxes2()
	{
		//for (size_t i = 0; i < 4; i++)
		//{
		//	mBoxes[i]->SetState(Dead);
		//}
	}
	void UI_FocusBoxes2::Initialize()
	{
		mTr = GetComp<Transform>();
		mTr->SetPosition(Vector3(0.0f, 0.0f, -2.0f));
		mAccDeltaTime = 0.0f;

		AddComp<SCRIPT_UI>();

		GameObject::Initialize();
	}
	void UI_FocusBoxes2::Update()
	{
		Vector3 ppos = Player->GetComp<Transform>()->GetPosition();

		if (mObjs.empty())
		{
			mBoxes[0]->SetState(GameObject::eState::Paused);
			mBoxes[1]->SetState(GameObject::eState::Paused);
			mBoxes[2]->SetState(GameObject::eState::Paused);
			mBoxes[3]->SetState(GameObject::eState::Paused);
		}
		else
		{
			mBoxes[0]->SetState(this->GetState());
			mBoxes[1]->SetState(this->GetState());
			mBoxes[2]->SetState(this->GetState());
			mBoxes[3]->SetState(this->GetState());
		}


		std::map<float, GameObject*> distanceMap = {};
		for (GameObject* obj : mObjs)
		{
			if (obj->GetState() == Active)
			{
				Transform* tr = obj->GetComp<Transform>();
				Vector3 objpos = tr->GetPosition();

				float answer = sqrt(pow(objpos.x - ppos.x, 2)
					+ pow(objpos.y - ppos.y, 2));

				distanceMap.insert(std::make_pair(answer, obj));
			}
		}
		GameObject* prevobj = mObj;
		if (prevobj)
			prevobj->SetSelected(false);
		if (distanceMap.empty() == false)
		{
			mObj = distanceMap.begin()->second;
			mObj->SetSelected(true);
		}
		else
		{
			mObj = nullptr;
		}
		mAccDeltaTime += Time::DeltaTime() * mDir;

		if (fabs(mAccDeltaTime) > 8.0f)
		{
			mDir *= -1.0f;
		}

		if (mObj)
		{
			mBoxes[0]->SetState(GameObject::eState::Active);
			mBoxes[1]->SetState(GameObject::eState::Active);
			mBoxes[2]->SetState(GameObject::eState::Active);
			mBoxes[3]->SetState(GameObject::eState::Active);

			Vector3 objpos = mObj->GetComp<Transform>()->GetPosition();
			Vector3 objscale = mObj->GetComp<Transform>()->GetScale();

			Vector3 p0 = Vector3(objpos.x - objscale.x * 0.5f - 1.5f, objpos.y + objscale.y * 0.5f, -2.0f);
			Vector3 p1 = Vector3(objpos.x + objscale.x * 0.5f + 1.5f, objpos.y + objscale.y * 0.5f, -2.0f);
			Vector3 p2 = Vector3(objpos.x - objscale.x * 0.5f - 1.5f, objpos.y - objscale.y * 0.5f, -2.0f);
			Vector3 p3 = Vector3(objpos.x + objscale.x * 0.5f + 1.5f, objpos.y - objscale.y * 0.5f, -2.0f);

			Vector3 pp0 = p0 - objpos;
			Vector3 pp1 = p1 - objpos;
			Vector3 pp2 = p2 - objpos;
			Vector3 pp3 = p3 - objpos;

			pp0.Normalize();
			pp1.Normalize();
			pp2.Normalize();
			pp3.Normalize();

			mBoxes[0]->GetComp<Transform>()->SetPosition(p0 + pp0 * (mAccDeltaTime * 0.3f));
			mBoxes[1]->GetComp<Transform>()->SetPosition(p1 + pp1 * (mAccDeltaTime * 0.3f));
			mBoxes[2]->GetComp<Transform>()->SetPosition(p2 + pp2 * (mAccDeltaTime * 0.3f));
			mBoxes[3]->GetComp<Transform>()->SetPosition(p3 + pp3 * (mAccDeltaTime * 0.3f));
		}
		else
		{
			mBoxes[0]->SetState(GameObject::eState::Paused);
			mBoxes[1]->SetState(GameObject::eState::Paused);
			mBoxes[2]->SetState(GameObject::eState::Paused);
			mBoxes[3]->SetState(GameObject::eState::Paused);
		}

		GameObject::Update();
	}
	void UI_FocusBoxes2::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void UI_FocusBoxes2::Render()
	{
		GameObject::Render();
	}
	void UI_FocusBoxes2::SetSelectObj(GameObject* obj)
	{
		GameObject* prevobj = mObj;
		mObj = obj;
		prevobj->SetSelected(false);
		mObj->SetSelected(true);

		Vector3 objpos = obj->GetComp<Transform>()->GetPosition();
		Vector3 objscale = obj->GetComp<MeshRenderer>()->GetImgScale();

		mBoxes[0]->GetComp<Transform>()->SetPosition(Vector3(objpos.x - objscale.x * 0.5f - 1.5f, objpos.y + objscale.y * 0.5f, -2.0f));
		mBoxes[1]->GetComp<Transform>()->SetPosition(Vector3(objpos.x + objscale.x * 0.5f + 1.5f, objpos.y + objscale.y * 0.5f, -2.0f));
		mBoxes[2]->GetComp<Transform>()->SetPosition(Vector3(objpos.x - objscale.x * 0.5f - 1.5f, objpos.y - objscale.y * 0.5f, -2.0f));
		mBoxes[3]->GetComp<Transform>()->SetPosition(Vector3(objpos.x + objscale.x * 0.5f + 1.5f, objpos.y - objscale.y * 0.5f, -2.0f));

	}
	void UI_FocusBoxes2::DeleteSelectobj(GameObject* gobj)
	{
		 std::vector<GameObject*>::iterator iter = mObjs.begin();
    while (iter != mObjs.end())
    {
        GameObject* obj = *iter;
        if (obj == gobj)
        {
            iter = mObjs.erase(iter); // erase returns the iterator following the last removed element
        }
        else
        {
            ++iter;
        }
    }
	}
}