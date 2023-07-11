#pragma once
#include "Gobj_Interactable.h"

namespace sg
{
	class Interact_LobbyCharacter : public Gobj_Interactable
	{
	public:
		Interact_LobbyCharacter();
		~Interact_LobbyCharacter();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:

	};
}
