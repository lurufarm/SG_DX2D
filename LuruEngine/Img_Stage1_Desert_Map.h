#pragma once
class Img_Stage0_Desert_Map
{
};

#pragma once
#include "Gobj_Img.h"

namespace sg
{
	class Img_Stage1_Map : public Gobj_Img
	{
	public:

		enum class Stage1
		{
			desert01,
			desert02,
			desert03,
			desert04,
			desertmidboss,
		};

		Img_Stage1_Map(Stage1 num);
		~Img_Stage1_Map();


		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
		Stage1 mNum;

	};
}
