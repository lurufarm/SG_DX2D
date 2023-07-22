#include "Bullet_CheeseArrow.h"

namespace sg
{
	Bullet_CheeseArrow::Bullet_CheeseArrow()
	{
	}
	Bullet_CheeseArrow::~Bullet_CheeseArrow()
	{
	}
	void Bullet_CheeseArrow::Initialize()
	{
		mType = eBulletType::Basic;
		SetMesh();
		SetMaterial(L"Arrow");
		mMr->Initialize();
		
	}
	void Bullet_CheeseArrow::Update()
	{
	}
	void Bullet_CheeseArrow::LateUpdate()
	{
	}
	void Bullet_CheeseArrow::Render()
	{
	}
}