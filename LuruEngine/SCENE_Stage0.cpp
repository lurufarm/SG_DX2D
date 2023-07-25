#include "SCENE_Stage0.h"
#include "Gobj_Player.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	SCENE_Stage0::SCENE_Stage0()
	{
	}
	SCENE_Stage0::~SCENE_Stage0()
	{
	}
	void SCENE_Stage0::Initialize()
	{
		PlayScene::Initialize();
	}
	void SCENE_Stage0::Update()
	{
		PlayScene::Update();
	}
	void SCENE_Stage0::LateUpdate()
	{
		PlayScene::LateUpdate();
	}
	void SCENE_Stage0::Render()
	{
		PlayScene::Render();
	}
	void SCENE_Stage0::OnEnter()
	{
		float BgColor[3] = { 0.5f, 0.5f, 0.5f };
		GetDevice()->SetBgColor(BgColor);
		renderer::mainCamera = mCamera;
		AddGameObj(eLayerType::Player, Player);
	}
	void SCENE_Stage0::OnExit()
	{
	}
}