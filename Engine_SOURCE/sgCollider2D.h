#pragma once
#include "sgComponent.h"
#include "sgTransform.h"

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

		void SetType(eColliderType type) { mType = type; }
		void SetSize(Vector2 size) { mSize = size; }
		void SetCenter(Vector2 size) { mCenter = size; }

	private:
		eColliderType mType;
		Transform* mCTr;

		Vector2 mSize;
		Vector2 mCenter;

	};
}
