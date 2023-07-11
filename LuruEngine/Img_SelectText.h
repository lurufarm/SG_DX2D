#pragma once
#include "Gobj_Img.h"

namespace sg
{
	class Img_SelectText : public Gobj_Img
	{
	public:

		Img_SelectText(bool type);
		~Img_SelectText();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:

		bool mType;
	};
}
