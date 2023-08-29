#pragma once
#include "Gobj_Img.h"

namespace sg
{

	class Img_StartingPlate : public Gobj_Img
	{
	public:
		Img_StartingPlate();
		~Img_StartingPlate();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};

}