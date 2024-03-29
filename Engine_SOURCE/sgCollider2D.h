#pragma once
#include "sgComponent.h"
#include "sgTransform.h"
#include "sgRenderer.h"

namespace sg
{
	class Collider2D : public Component
	{
	public:
		Collider2D();
		~Collider2D();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void OnCollisionEnter(Collider2D* other);
		void OnCollisionStay(Collider2D* other);
		void OnCollisionExit(Collider2D* other);

		void SetType(eColliderType type) { mType = type; }
		void SetSize(Vector2 size) { mSize = size; }
		void SetCenter(Vector2 centerpos) { mCenter = centerpos; }
		void SetRot(float rot) { mRotation = rot; }
		UINT GetColliderID() { return mColliderID; }

		Vector3 GetCPosition() { return mPosition; }
		Vector2 GetCenter() { return mCenter; }
		Vector2 GetCSize() { return mSize; }
		Vector3 GetCScale() { return mScale; }

		renderer::MyCB GetMyCB() { return mCB; }


	private:
		static UINT mColliderNumber;
		UINT mColliderID;
		eColliderType mType;
		Transform* mCTr;
		
		Vector3 mPosition;
		Vector2 mSize;
		Vector2 mCenter;
		Vector3 mScale;
		float mRotation;

		renderer::MyCB mCB;
	};
}
