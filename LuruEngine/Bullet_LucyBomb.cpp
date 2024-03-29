#include "Bullet_LucyBomb.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "Gobj_Player.h"
#include "SCRIPT_Bullet.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	Bullet_LucyBomb::Bullet_LucyBomb()
	{
		SetName(L"LucyBomb");
		mThisNum = 1;
		Bullet_LucyBomb::Initialize();
	}
	Bullet_LucyBomb::Bullet_LucyBomb(int num)
	{
		SetName(L"LucyBomb");
		mThisNum = num;
		Bullet_LucyBomb::Initialize();
	}
	Bullet_LucyBomb::~Bullet_LucyBomb()
	{
	}
	void Bullet_LucyBomb::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		mAni = AddComp<Animator>();
		mCol = GetComp<Collider2D>();
		mType = eBulletType::Lucy;
		SetMesh();
		SetMaterial(L"AnimationMaterial");

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"LucyBomb", L"..\\Resources\\Character\\Lucy\\LucyBomb.png");
		mAni->Create(L"Ani_LucyBomb", atlas, Vector2::Zero, Vector2(15.0f, 15.0f), 4, Vector2::Zero, 0.1f);
		mMr->Initialize();
		mAni->PlayAnimation(L"Ani_LucyBomb", true, true);

		mCol->SetSize(Vector2(0.7f, 0.7f));

		mBulletOwner = SceneManager::GetChar(L"Lucy");
		Gobj_Bullet::Initialize();

		AddComp<SCRIPT_Bullet>();
	}
	void Bullet_LucyBomb::Update()
	{
		Gobj_Bullet::Update();
	}
	void Bullet_LucyBomb::LateUpdate()
	{
		Gobj_Bullet::LateUpdate();
	}
	void Bullet_LucyBomb::Render()
	{
		Gobj_Bullet::Render();
	}
}