#pragma once
#include "Gobj_Img.h"

namespace sg
{

	class Img_RewardPlate : public Gobj_Img
	{
	public:
		Img_RewardPlate();
		~Img_RewardPlate();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};

}