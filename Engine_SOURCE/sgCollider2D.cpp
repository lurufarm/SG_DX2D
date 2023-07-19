#include "sgCollider2D.h"
#include "sgGameObject.h"
#include "sgRenderer.h"

namespace sg
{
	UINT Collider2D::mColliderNumber = 0;
	Collider2D::Collider2D()
		: Component(eComponentType::Collider2D)
		, mCTr(nullptr)
		, mSize(Vector2::One)
		, mCenter(Vector2::Zero)
	{
		mColliderNumber++;
		mColliderID = mColliderNumber;
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
		Transform* tr = GetOwner()->GetComp<Transform>();

		mScale = tr->GetScale();
		mScale.x *= mSize.x;
		mScale.y *= mSize.y;

		Vector3 pos = tr->GetPosition();
		pos.x += mCenter.x;
		pos.y += mCenter.y;
		
		mPosition = pos;

		graphics::DebugMesh mesh = {};
		mesh.position = pos;
		mesh.scale = mScale;
		mesh.rotation = tr->GetRotation();
		mesh.type = eColliderType::Rect;
		mesh.MyCBType = mCB.ColliderColor;

		renderer::PushDebugMeshAttribute(mesh);
	}
	void Collider2D::Render()
	{
	}
	void Collider2D::OnCollisionEnter(Collider2D* other)
	{
		mCB.ColliderColor = true;
		other->mCB.ColliderColor = true;

		const std::vector<Script*>& scripts
			= GetOwner()->GetComps<Script>();

		for (Script* script : scripts)
		{
			script->OnCollisionEnter(other);
		}
	}
	void Collider2D::OnCollisionStay(Collider2D* other)
	{
		const std::vector<Script*>& scripts
			= GetOwner()->GetComps<Script>();

		for (Script* script : scripts)
		{
			script->OnCollisionStay(other);
		}
	}
	void Collider2D::OnCollisionExit(Collider2D* other)
	{
		mCB.ColliderColor = false;
		other->mCB.ColliderColor = false;

		const std::vector<Script*>& scripts
			= GetOwner()->GetComps<Script>();

		for (Script* script : scripts)
		{
			script->OnCollisionExit(other);

		}
	}
}