#pragma once
#include "Gobj_BGImg.h"

namespace sg
{
	class TitleImg01 : public Gobj_BGImg
	{
	public:
		TitleImg01();
		~TitleImg01();

		 void Initialize();
		 void Update();
		 void LateUpdate();
		 void Render();
		
	private:
		//Transform* mTr;
		//MeshRenderer* mMr;
	};
}
