#pragma once
#include "Gobj_Img.h"

namespace sg
{
	class Img_Title : public Gobj_Img
	{
	public:
		Img_Title();
		~Img_Title();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();
		
	private:
	};
}
