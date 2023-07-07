#pragma once
#include "../Engine_SOURCE/sgScript.h"
#include "../Engine_SOURCE/sgCamera.h"

namespace sg
{
	class SCRIPT_GridScript : public Script
	{
	public:
		SCRIPT_GridScript();
		~SCRIPT_GridScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetCamera(Camera* camera) { mCamera = camera; }

	private:
		Camera* mCamera;
	};
}
