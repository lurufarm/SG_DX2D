#pragma once
#include "Gobj_Img.h"

namespace sg
{
	class Img_Stage0_Forest01_Map : public Gobj_Img
	{
	public:
		
		enum class ForestFd
		{
			forest01,
			forest02,
			forest03,
			forest04,
			forest05,
			forest06,
			end,
		};

		Img_Stage0_Forest01_Map(ForestFd num);
		~Img_Stage0_Forest01_Map();


		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
		ForestFd mNum;

	};
}
