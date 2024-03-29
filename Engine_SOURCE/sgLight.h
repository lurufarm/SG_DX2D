#pragma once
#include "sgComponent.h"
#include "sgGraphics.h"

namespace sg
{
	using namespace sg::graphics;
	class Light : public Component
	{
	public:
		Light();
		~Light();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		LightAttribute GetAttribute() { return mAttribute; }
		void SetType(eLightType type) { mAttribute.type = type; }
		void SetRadius(float radius) { mAttribute.radius = radius; }
		void SetAngle(float angle) { mAttribute.angle = angle; }
		void SetColor(Vector4 color) { mLightColor = color; }
		Vector4 GetColor() { return mAttribute.color; }
		eLightType GetType() { return mAttribute.type; }
		float GetRadius() { return mAttribute.radius; }
		float GetAngle() { return mAttribute.angle; }

		void SetLightPos(Vector3 pos) { mLightPos = pos; }

		static void ClearNum() { mNum = 0; }

		void SetLightOn() { mOn = true; }
		void SetLightOff() { mOn = false; }
		bool GetLightState() { return mOn; }

	private:
		bool mOn;
		bool mPlus;
		LightAttribute mAttribute;

		Vector3 mLightPos;
		Vector4 mLightColor;
		static int mNum;

		class Scene* mScene;

	};
}
