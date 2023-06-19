#pragma once
#include "sgScene.h"

namespace sg
{
	class PlayScene : public Scene
	{
	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}

class PlayScene
{
};
