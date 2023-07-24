#pragma once
#include "Gobj_Interactable.h"

namespace sg
{
	class Interact_LobbyGate : public Gobj_Interactable
	{
	public:
		Interact_LobbyGate();
		~Interact_LobbyGate();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
		class Animator* mAni;
	};

}