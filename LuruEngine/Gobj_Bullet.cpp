#include "Gobj_Bullet.h"
#include "..\Engine_SOURCE\sgTransform.h"

namespace sg
{
	Gobj_Bullet::Gobj_Bullet()
	{
		mType = eBulletType::Basic;
		AddComp<MeshRenderer>();
		AddComp<Collider2D>();
	}
	Gobj_Bullet::~Gobj_Bullet()
	{
	}
	void Gobj_Bullet::initialize()
	{
		GameObject::Initialize();
	}
	void Gobj_Bullet::Update()
	{
		GameObject::Update();
	}
	void Gobj_Bullet::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Gobj_Bullet::Render()
	{
	}
}