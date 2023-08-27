#include "Bullet_CheeseArrow.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "Gobj_Player.h"
#include "SCRIPT_Bullet.h"
#include "SCRIPT_Player.h"
#include "Gobj_Character.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	Bullet_CheeseArrow::Bullet_CheeseArrow()
	{
		SetName(L"CheeseArrow");
		Bullet_CheeseArrow::Initialize();
	}
	Bullet_CheeseArrow::~Bullet_CheeseArrow()
	{
	}
	void Bullet_CheeseArrow::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		mType = eBulletType::Cheese;
		SetMesh();
		SetMaterial(L"Arrow");
		mMr->Initialize();

		mBulletOwner = SceneManager::GetChar(L"Cheese");
		Gobj_Bullet::Initialize();

		AddComp<SCRIPT_Bullet>();
	}
	void Bullet_CheeseArrow::Update()
	{
		Gobj_Bullet::Update();
	}
	void Bullet_CheeseArrow::LateUpdate()
	{
		Gobj_Bullet::LateUpdate();
	}
	void Bullet_CheeseArrow::Render()
	{
		Gobj_Bullet::Render();
	}
}