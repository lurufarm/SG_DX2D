#include "UI_HpBar.h"
#include "Gobj_Player.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	UI_HPBar::UI_HPBar()
	{
		SetName(L"HPBar");
		mMowner = nullptr;
		UI_HPBar::Initialize();
	}
	UI_HPBar::~UI_HPBar()
	{
	}
	void UI_HPBar::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp <MeshRenderer>();
		SetMesh();
		SetMaterial(L"UIHPBar");
		mMr->Initialize();
	}
	void UI_HPBar::Update()
	{
		Vector3 pos = Vector3::Zero;
		if (mMowner)
		{
			if (mMowner->GetState() == eState::Active)
			{
				SetState(eState::Active);
				pos = mMowner->GetComp<Transform>()->GetPosition();
				pos.y += 10.0f;
				mTr->SetPosition(pos);
			}
			else if (mMowner->GetState() == eState::Dead)
				SetState(eState::Dead);
			else if (mMowner->GetState() == eState::Paused)
				SetState(eState::Paused);
		}
		else
		{
			pos = Player->GetComp<Transform>()->GetPosition();
			pos.y += 10.0f;
			mTr->SetPosition(pos);
		}
		Gobj_UI::Update();
	}
	void UI_HPBar::LateUpdate()
	{
		Gobj_UI::LateUpdate();
	}
	void UI_HPBar::Render()
	{
		BindConstantBuffer();
		Gobj_UI::Render();
	}
	void UI_HPBar::BindConstantBuffer()
	{
		if (mMowner)
		{
			if (mMowner->GetState() == eState::Active)
			{
				mCB.maxHP = mMowner->GetStat().mMaxHP;
				mCB.curHP = mMowner->GetStat().mCurHP;
			}
		}
		else
		{
			mCB.maxHP = Player->GetStat().mMaxHP;
			mCB.curHP = Player->GetStat().mCurHP;
		}

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::HPBar];
		cb->SetData(&mCB);
		cb->Bind(eShaderStage::PS);
	}
}