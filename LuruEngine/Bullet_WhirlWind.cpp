#include "Bullet_WhirlWind.h"
#include "SCRIPT_MobProjectile.h"

namespace sg
{
	Bullet_WhirlWind::Bullet_WhirlWind(Gobj_Monster* BulletOwner)
	{
		SetName(L"WhirlWind");
		this->SetProjOwner(BulletOwner);
		mProjOwner = BulletOwner;

		Bullet_WhirlWind::Initialize();
	}
	Bullet_WhirlWind::~Bullet_WhirlWind()
	{
	}
	void Bullet_WhirlWind::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mType = eMProjType::WhirlWind;
		Animator* mAni = AddComp<Animator>();
		SetMesh();
		SetMaterial(L"AnimationMaterial");

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"WhirlWind", L"..\\Resources\\Monster\\Whirlwind.png");
		mAni->Create(L"Ani_WhirlWind", atlas, Vector2::Zero, Vector2(17.0f, 19.0f), 5, Vector2::Zero, 0.07f);
		mMr->Initialize();
		mAni->PlayAnimation(L"Ani_WhirlWind", true, true);

		mCol->SetSize(Vector2(0.8f, 0.8f));

		AddComp<SCRIPT_MobProjectile>();

	}
	void Bullet_WhirlWind::Update()
	{
		Gobj_MobProjectile::Update();
	}
	void Bullet_WhirlWind::LateUpdate()
	{
		Gobj_MobProjectile::LateUpdate();
	}
	void Bullet_WhirlWind::Render()
	{
		Gobj_MobProjectile::Render();
	}
}