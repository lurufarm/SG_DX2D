#include "Bullet_BigGreenOrb.h"

#include "Bullet_FireOrbs.h"
#include "Bullet_FireOrb.h"
#include "sgObject.h"
#include <random>

namespace sg
{
	Bullet_BigGreenOrb::Bullet_BigGreenOrb(Gobj_Monster* BulletOwner)
	{
		SetName(L"BigGreenOrb");
		mProjOwner = BulletOwner;
		mFirstPos = mProjOwner->GetComp<Transform>()->GetPosition();

		Bullet_BigGreenOrb::Initialize();
	}
	Bullet_BigGreenOrb::~Bullet_BigGreenOrb()
	{
		RandAngle();
		mAngle *= (3.141592 / 180.0f);

		for (size_t i = 0; i < 12; i++)
		{
			float a = i * 30;
			float added_angle = a * (3.141592 / 180.0f);
			float x = cos(mAngle + added_angle);
			float y = sin(mAngle + added_angle);

			mBullets[i] = object::GreenOrb(Vector2(x, y), this);
			mBullets[i]->SetFirstPos(mTr->GetPosition());
		}
	}
	void Bullet_BigGreenOrb::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mAni = AddComp<Animator>();
		mCol = GetComp<Collider2D>();
		mType = eMProjType::BigOrb;
		SetMesh();
		SetMaterial(L"AnimationMaterial");
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"BigGreenOrb", L"..\\Resources\\Monster\\Bosses\\BigGreenOrb.png");
		mAni->Create(L"Ani_BigGreenOrb", atlas, Vector2::Zero, Vector2(20.0f, 20.0f), 3, Vector2::Zero, 0.05f);
		mMr->Initialize();
		mAni->PlayAnimation(L"Ani_BigGreenOrb", true, true);

		AddComp<SCRIPT_MobProjectile>();
	}
	void Bullet_BigGreenOrb::Update()
	{
		GameObject::Update();
	}
	void Bullet_BigGreenOrb::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Bullet_BigGreenOrb::Render()
	{
		GameObject::Render();
	}
	void Bullet_BigGreenOrb::RandAngle()
	{
		std::random_device rd;  // 랜덤 시드를 얻기 위한 장치
		std::mt19937 gen(rd());  // 메르센 트위스터 난수 생성기 초기화
		std::uniform_int_distribution<> dist(0, 30);  // 0과 1 사이의 균등 분포

		mAngle = dist(gen);
	}
}