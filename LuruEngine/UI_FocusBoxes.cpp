#include "UI_FocusBoxes.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgTime.h"
#include "..\Engine_SOURCE\sgScene.h"
#include "..\Engine_SOURCE\sgObject.h"

namespace sg
{
	UI_FocusBoxes::UI_FocusBoxes(Scene* myscene)
		: mObj(nullptr)
		, mObjs{}
		, mMyScene(myscene)
	{
		SetName(L"Gobj_FocusBoxes");

		mObjs.clear();
		//mMyScene = myscene;

		mBoxes[0] = object::Instantiate<UI_FocusBox>(0, eLayerType::UI, mMyScene);
		mBoxes[1] = object::Instantiate<UI_FocusBox>(1, eLayerType::UI, mMyScene);
		mBoxes[2] = object::Instantiate<UI_FocusBox>(2, eLayerType::UI, mMyScene);
		mBoxes[3] = object::Instantiate<UI_FocusBox>(3, eLayerType::UI, mMyScene);

		UI_FocusBoxes::Initialize();
	}
	UI_FocusBoxes::~UI_FocusBoxes()
	{
		for (size_t i = 0; i < 4; i++)
		{
			mBoxes[i]->SetState(Dead);
		}
	}
	void UI_FocusBoxes::Initialize()
	{
		mTr = GetComp<Transform>();
		mTr->SetPosition(Vector3(0.0f, 0.0f, -2.0f));
		mAccDeltaTime = 0.0f;

		GameObject::Initialize();
	}
	void UI_FocusBoxes::Update()
	{
		mBoxes[0]->SetState(this->GetState());
		mBoxes[1]->SetState(this->GetState());
		mBoxes[2]->SetState(this->GetState());
		mBoxes[3]->SetState(this->GetState());


		if (mObj != nullptr)
		{

			mAccDeltaTime += Time::DeltaTime() * mDir;

			if (fabs(mAccDeltaTime) > 5.0f)
			{
				mDir *= -1.0f;
			}

			Vector3 objpos = mObj->GetComp<Transform>()->GetPosition();
			Vector3 objscale = mObj->GetComp<MeshRenderer>()->GetImgScale();

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

			mBoxes[0]->GetComp<Transform>()->SetPosition(p0 + pp0 * mAccDeltaTime);
			mBoxes[1]->GetComp<Transform>()->SetPosition(p1 + pp1 * mAccDeltaTime);
			mBoxes[2]->GetComp<Transform>()->SetPosition(p2 + pp2 * mAccDeltaTime);
			mBoxes[3]->GetComp<Transform>()->SetPosition(p3 + pp3 * mAccDeltaTime);

			UINT now = mObj->GetOrder();

			if (Input::KeyD(eKeyCode::A))
			{
				if (now >= 2)
				{
					GameObject* prevobj = mObj;
					if (prevobj)
						prevobj->SetSelected(false);

					this->Initialize();
					now--;
					std::map<UINT, GameObject*>::iterator iter = mObjs.find(now);
					mObj = iter->second;
					mObj->SetSelected(true);
				}
			}
			else if (Input::KeyD(eKeyCode::D))
			{
				std::map<UINT, GameObject*>::iterator upperBoundIter = mObjs.upper_bound(now);
				if (upperBoundIter != mObjs.end())
				{
					GameObject* prevobj = mObj;
					if (prevobj)
						prevobj->SetSelected(false);
					this->Initialize();
					now = upperBoundIter->first;
					std::map<UINT, GameObject*>::iterator iter = mObjs.find(now);
					if (iter != mObjs.end())
					{
						mObj = iter->second;
						mObj->SetSelected(true);
					}
				}
			}
		}

		GameObject::Update();
	}
	void UI_FocusBoxes::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void UI_FocusBoxes::Render()
	{
		GameObject::Render();	
	}
	void UI_FocusBoxes::SetSelectObj(GameObject* obj)
	{
		mObj = obj;

		Vector3 objpos = obj->GetComp<Transform>()->GetPosition();
		Vector3 objscale = obj->GetComp<MeshRenderer>()->GetImgScale();

		mBoxes[0]->GetComp<Transform>()->SetPosition(Vector3(objpos.x - objscale.x * 0.5f - 1.5f, objpos.y + objscale.y * 0.5f, -2.0f));
		mBoxes[1]->GetComp<Transform>()->SetPosition(Vector3(objpos.x + objscale.x * 0.5f + 1.5f, objpos.y + objscale.y * 0.5f, -2.0f));
		mBoxes[2]->GetComp<Transform>()->SetPosition(Vector3(objpos.x - objscale.x * 0.5f - 1.5f, objpos.y - objscale.y * 0.5f, -2.0f));
		mBoxes[3]->GetComp<Transform>()->SetPosition(Vector3(objpos.x + objscale.x * 0.5f + 1.5f, objpos.y - objscale.y * 0.5f, -2.0f));
																							
	}
}