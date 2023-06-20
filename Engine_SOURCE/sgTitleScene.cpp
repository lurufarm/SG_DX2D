#include "sgTitleScene.h"
#include "sgTransform.h"
#include "sgMeshRenderer.h"
#include "sgResources.h"
#include "sgMesh.h"

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
		GameObject* player = new GameObject();
		AddGameObj(eLayerType::Player, player);
		MeshRenderer* mr = player->AddComp<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));

		//GameObject* player2 = new GameObject();
		//AddGameObj(eLayerType::Player, player2);
		//player2->AddComp<MeshRenderer>();

		//Transform* tr = player2->GetComp<Transform>();
		//tr->SetPosition(Vector3(0.5f, 0.5f, 0.0f));

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