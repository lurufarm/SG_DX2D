#pragma once
#include "Gobj_Img.h"

namespace sg
{
	class Img_LobbyMolding : public Gobj_Img
	{
	public:
		Img_LobbyMolding();
		~Img_LobbyMolding();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
