#pragma once
#include "Gobj_Img.h"

namespace sg
{
	class Img_LobbyTorch : public Gobj_Img
	{
	public:
		Img_LobbyTorch();
		~Img_LobbyTorch();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
		class Animator* mAni;
		class Light* mLg;

	};
}
