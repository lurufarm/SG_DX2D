#pragma once
#include "Gobj_Interactable.h"

namespace sg
{
	class Interact_LobbyUpgrade : public Gobj_Interactable
	{
	public:
		Interact_LobbyUpgrade();
		~Interact_LobbyUpgrade();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
