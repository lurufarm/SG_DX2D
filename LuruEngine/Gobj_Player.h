#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"
#include "Gobj_Character.h"

namespace sg
{
	class Gobj_Player : public GameObject
	{
	public:
		Gobj_Player();
		~Gobj_Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

		Gobj_Character* mChar;
		std::vector<Gobj_Character*> mCompanies;

	};
}
