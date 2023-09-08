#include "Img_RewardPlate.h"
#include "..\\Engine_SOURCE\sgSceneManager.h"
#include "SCENE_PlayScene.h"

namespace sg
{
	Img_RewardPlate::Img_RewardPlate()
	{
		std::wstring name = Gobj_Img::GetName();
		name += L"_RewardPlate";
		SetName(name);
		Img_RewardPlate::Initialize();
	}
	Img_RewardPlate::~Img_RewardPlate()
	{
	}
	void Img_RewardPlate::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		SetMesh();
		SetMaterial(L"ImgRewardPlate0");
		mMr->Initialize();
	}
	void Img_RewardPlate::Update()
	{
		Scene* sc = SceneManager::GetActiveScene();

		if (dynamic_cast<PlayScene*>(sc)->IsFinished())
			SetMaterial(L"ImgRewardPlate1");

		Gobj_Img::Update();
	}
	void Img_RewardPlate::LateUpdate()
	{
		Gobj_Img::LateUpdate();
	}
	void Img_RewardPlate::Render()
	{
		Gobj_Img::Render();
	}
}