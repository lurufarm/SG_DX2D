#include "sgRenderer.h"
#include "sgInput.h"
#include "sgTime.h"

#include "sgResources.h"
#include "sgTexture.h"

namespace renderer
{
	using namespace sg;
	using namespace sg::graphics;

	Vertex vertexes[4] = {};
	sg::Mesh* mesh = nullptr;
	sg::Shader* shader = nullptr;
	sg::graphics::ConstantBuffer* constantBuffer = nullptr;

	void SetupState()
	{
		// Input Layout 정점 구조를 정보를 넘겨준다.
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {};

		arrLayout[0].AlignedByteOffset = 0;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		arrLayout[2].AlignedByteOffset = 28;
		arrLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayout[2].InputSlot = 0;
		arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[2].SemanticName = "TEXCOORD";
		arrLayout[2].SemanticIndex = 0;

		sg::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());
	}
	
	void LoadBuffer()
	{
		// Vertex Buffer 설정
		mesh = new sg::Mesh();
		mesh->CreateVertexBuffer(vertexes, 4);

		// Index Buffer 설정
		std::vector<UINT> indexes = {};
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());

		// Constant Buffer 설정
		constantBuffer = new ConstantBuffer(eCBType::Transform);
		constantBuffer->Create(sizeof(Vector4));

		//constantBuffer->SetData(&MovePos);
		//constantBuffer->Bind(eShaderStage::VS);

	}
	
	void LoadShader()
	{
		shader = new sg::Shader();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
	}

	void Initialize()
	{
		vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		LoadBuffer();
		LoadShader();
		SetupState();

		Texture* texture
			= Resources::Load<Texture>(L"Cat", L"..\\Resources\\Texture\\Cat.png");

		texture->BindShader(eShaderStage::PS, 0);

	}
	void Update()
	{
		//if (Input::KeyP(eKeyCode::W) || Input::KeyD(eKeyCode::W))
		//{
		//	MovePos.y += 0.5 * Time::DeltaTime();
		//}
		//else if (Input::KeyP(eKeyCode::S) || Input::KeyD(eKeyCode::S))
		//{
		//	MovePos.y -= 0.5 * Time::DeltaTime();
		//}
		//if (Input::KeyP(eKeyCode::A) || Input::KeyD(eKeyCode::A))
		//{
		//	MovePos.x -= 0.5 * Time::DeltaTime();
		//}
		//else if (Input::KeyP(eKeyCode::D) || Input::KeyD(eKeyCode::D))
		//{
		//	MovePos.x += 0.5 * Time::DeltaTime();
		//}

		//constantBuffer->SetData(&MovePos);
	}

	void Release()
	{
		delete mesh;
		delete shader;
		delete constantBuffer;
	}
}