#pragma once
#include "sgComponent.h"

namespace sg
{
	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void BindConstantBuffer();

		void SetPosition(Vector3 pos) { mPosition = pos; }
		void SetRotation(Vector3 rot) 
		{ 
			if (rot.z <= 1.0f && rot.z >= 0.0f)
			{
				mRotation = rot;

			}
			else
			{
				const float PI = 3.141592;
				mRotation.z = rot.z * PI / 180;
			}
		}
		void SetScale(Vector3 scale) {
			mScale = scale;
			int a = 0;
		}

		void SetPosition(float x, float y, float z) { mPosition = Vector3(x, y, z); }
		void SetRotation(float x, float y, float z) { mRotation = Vector3(x, y, z); }
		void SetScale(float x, float y, float z) { mScale = Vector3(x, y, z); }

		Vector3 GetPosition() { return mPosition; }
		Vector3 GetRotation() { return mRotation; }
		Vector3 GetRotaitioAsDegree() 
		{
			Vector3 degree;

			const float PI = 3.141592;

			degree.x = mRotation.x / PI * 180;
			degree.y = mRotation.x / PI * 180;
			degree.z = mRotation.x / PI * 180;
			
			return degree;
		}
		Vector3 GetScale() { return mScale; }

		Vector3 Forward() { return mForward; }
		Vector3 Right() { return mRight; }
		Vector3 Up() { return mUp; }

		void SetParent(Transform* transform) { mParent = transform; }
		Transform* GetParent() { return mParent; }
		Matrix& GetMatrix() { return mWorld; }


	private:
		Vector3 mPosition;
		Vector3 mRotation;
		Vector3 mScale;

		Vector3 mUp;
		Vector3 mForward;
		Vector3 mRight;

		Matrix mWorld;

		Transform* mParent;
	};
}

