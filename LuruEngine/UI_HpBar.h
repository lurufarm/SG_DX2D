#pragma once
#include "Gobj_UI.h"

namespace sg
{
	class Gobj_Monster;
	class UI_HPBar : public Gobj_UI
	{
	public:
		UI_HPBar();
		~UI_HPBar();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void SetHPBarOwner(Gobj_Monster* owner) { mMowner = owner; }

		void BindConstantBuffer();

	private:

		Gobj_Monster* mMowner;
		renderer::HPBarCB mCB;
	};
}
