#pragma once
#include "Gobj_Img.h"

namespace sg
{
	class Img_BulletIcon : public Gobj_Img
	{
	public:
		Img_BulletIcon(int num);
		~Img_BulletIcon();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:

		int mIconNum;

	};
}
