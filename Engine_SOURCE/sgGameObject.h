#pragma once
#include "sgEntity.h"
#include "sgComponent.h"
namespace sg
{
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void SetState(eState state) { mState = state; }
		eState GetState() { return mState; }

	private:
		eState mState;
	};
}

