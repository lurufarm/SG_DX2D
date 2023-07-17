#pragma once
#include "Gobj_Interactable.h"

namespace sg
{
	class Interact_LobbyCardBook : public Gobj_Interactable
	{
	public:
		Interact_LobbyCardBook();
		~Interact_LobbyCardBook();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
	};
}
