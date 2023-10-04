#pragma once
#include "Gobj_Img.h"

namespace sg
{
	class Img_Stage0_Map : public Gobj_Img
	{
	public:
		
		enum class Stage0
		{
			forestfd01,
			forestfd02,
			forestfd03,
			forestfd04,
			forestdg01,
			forestdg02,
			forestdg03,
			forestdg04,
			forestboss01,
			end,
		};

		Img_Stage0_Map(Stage0 num);
		~Img_Stage0_Map();


		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
		Stage0 mNum;

	};
}
