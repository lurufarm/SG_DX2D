#pragma once
#include "Gobj_Img.h"

namespace sg
{
	class Img_CharIcon : public Gobj_Img
	{
	public:
		Img_CharIcon(int num);
		~Img_CharIcon();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		bool IsSelected() { return mSelected; }
		void SetSelected(bool value) { mSelected = value; }

	private:

		int mIconNum;
		bool mSelected;

	};
}
