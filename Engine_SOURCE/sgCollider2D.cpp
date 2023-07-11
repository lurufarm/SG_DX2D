#include "sgCollider2D.h"
#include "sgGameObject.h"

namespace sg
{
	Collider2D::Collider2D()
		: Component(eComponentType::Collider2D)
		, mCTr(nullptr)
		, mSize(Vector2::One)
		, mCenter(Vector2::Zero)
	{
	}
	Collider2D::~Collider2D()
	{
	}
	void Collider2D::Initialize()
	{
		mCTr = GetOwner()->GetComp<Transform>();
	}
	void Collider2D::Update()
	{
	}
	void Collider2D::LateUpdate()
	{
	}
	void Collider2D::Render()
	{
	}
}