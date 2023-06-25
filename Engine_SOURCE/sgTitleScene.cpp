#include "sgTitleScene.h"
#include "sgTransform.h"
#include "sgMeshRenderer.h"
#include "sgResources.h"
#include "sgMesh.h"

#include "sgCameraScript.h"
#include "sgCamera.h"

#include "Gobj_BGImg.h"
#include "BGImg_TitleImg01.h"

namespace sg
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		//GameObject* player = new GameObject();
		//AddGameObj(eLayerType::Player, player);
		//MeshRenderer* mr = player->AddComp<MeshRenderer>();
		//mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
		//player->GetComp<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		//player->AddComp<CameraScript>();

		TitleImg01* title01 = new TitleImg01();
		AddGameObj(eLayerType::Player, title01);
		//title01->AddComp<CameraScript>();
		//title01->Initialize();
		//MeshRenderer* mr2 = title01->AddComp<MeshRenderer>();
		//mr2->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//mr2->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
		//title01->GetComp<Transform>()->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
		//Transform* tr2 = title01->GetComp<Transform>();



		GameObject* camera = new GameObject();
		AddGameObj(eLayerType::Player, camera);
		camera->GetComp<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComp<Camera>();
		camera->AddComp<CameraScript>();
		//Scene::Initialize();
	}
	void TitleScene::Update()
	{
		Scene::Update();
	}
	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
}