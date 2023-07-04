#pragma once
#include "Gobj_Img.h"

namespace sg
{
	class Img_LobbyMap : public Gobj_Img
	{
	public:
		Img_LobbyMap();
		~Img_LobbyMap();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:

	};
}
