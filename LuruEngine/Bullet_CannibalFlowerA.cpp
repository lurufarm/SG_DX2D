#include "Bullet_CannibalFlowerA.h"
#include "Gobj_Player.h"
#include "SCRIPT_Bullet.h"
#include "SCRIPT_Player.h"
#include "Gobj_Character.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	Bullet_CannibalFlowerA::Bullet_CannibalFlowerA()
	{
		SetName(L"Bullet_CannibalFlowerA");
		Bullet_CannibalFlowerA::Initialize();
	}
	Bullet_CannibalFlowerA::~Bullet_CannibalFlowerA()
	{
	}
	void Bullet_CannibalFlowerA::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		mType = eBulletType::CannibalFlowerA;
		SetMesh();
		SetMaterial(L"Arrow");
		mMr->Initialize();

		mBulletOwner = Gobj_Character::GetChar(L"Cheese");
		Gobj_Bullet::initialize();

		AddComp<SCRIPT_Bullet>();


	}
	void Bullet_CannibalFlowerA::Update()
	{
		Gobj_Bullet::Update();
	}
	void Bullet_CannibalFlowerA::LateUpdate()
	{
		Gobj_Bullet::LateUpdate();
	}
	void Bullet_CannibalFlowerA::Render()
	{
		Gobj_Bullet::Render();
	}
}