#include "sgRenderer.h"
#include "sgInput.h"
#include "sgTime.h"

namespace renderer
{
	using namespace sg;

	Vertex vertexes[4] = {};
	Vertex square[4] = {};
	Vertex star[10] = {};
	
	sg::Mesh* mesh = nullptr;
	sg::Shader* shader = nullptr;
	sg::graphics::ConstantBuffer* constantBuffer = nullptr;

	Vector4 MovePos = { 0.0f, 0.0f, 0.0f, 1.0f };


	ID3D11Buffer* squareBuffer = nullptr;
	ID3D11Buffer* squareIdxBuffer = nullptr;

	ID3D11Buffer* starBuffer = nullptr;
	ID3D11Buffer* starIdxBuffer = nullptr;

	//Vector4 MovePos = { 0.0f, 0.0f, 0.0f, 1.0f };

	void SetupState()
	{
		// Input Layout 정점 구조를 정보를 넘겨준다.
		D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {};

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

		sg::graphics::GetDevice()->CreateInputLayout(arrLayout, 2
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
		constantBuffer = new sg::graphics::ConstantBuffer(eCBType::Transform);
		constantBuffer->Create(sizeof(Vector4) * 2);

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
		vertexes[0].pos = Vector3(-1.0f, 1.0f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[1].pos = Vector3(1.0f, 1.0f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[2].pos = Vector3(1.0f, -1.0f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		vertexes[3].pos = Vector3(-1.0f, -1.0f, 0.0f);
		vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		//MovePos = { 0.0f, 0.0f, 0.0f, 1.0f };

		//square[0].pos = Vector3(0.2f, 0.8f, 0.0f);
		//square[0].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		//square[1].pos = Vector3(0.8f, 0.8f, 0.0f);
		//square[1].color = Vector4(0.0f, 1.0f, 1.0f, 1.0f);
		//square[2].pos = Vector3(0.8f, 0.2f, 0.0f);
		//square[2].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		//square[3].pos = Vector3(0.2f, 0.2f, 0.0f);
		//square[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		//star[0].pos = Vector3(-0.5f, 0.8f, 0.0f);
		//star[0].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		//star[1].pos = Vector3(-0.4f, 0.6f, 0.0f);
		//star[1].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		//star[2].pos = Vector3(-0.2f, 0.5f, 0.0f);
		//star[2].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		//star[3].pos = Vector3(-0.3f, 0.35f, 0.0f);
		//star[3].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		//star[4].pos = Vector3(-0.3f, 0.1f, 0.0f);
		//star[4].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		//star[5].pos = Vector3(-0.5, 0.2f, 0.0f);
		//star[5].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		//star[6].pos = Vector3(-0.7f, 0.1f, 0.0f);
		//star[6].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		//star[7].pos = Vector3(-0.7f, 0.35f, 0.0f);
		//star[7].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		//star[8].pos = Vector3(-0.8f, 0.5f, 0.0f);
		//star[8].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		//star[9].pos = Vector3(-0.6f, 0.6f, 0.0f);
		//star[9].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);

		//std::vector<UINT>squareidx = { 0, 1, 2, 0, 2, 3};
		//std::vector<UINT>staridx = { 0, 1, 9, 1, 2, 3, 3, 4, 5, 5, 6, 7, 7, 8, 9, 1, 3, 5, 1, 5, 7, 1, 7, 9};

		LoadBuffer();
		LoadShader();
		SetupState();


	}
	void Update()
	{
		//if (Input::KeyP(eKeyCode::W) || Input::KeyD(eKeyCode::W))
		//{
		//	MovePos.y += 0.5 * Time::DeltaTime();
		//}
		//else if (Input::KeyP(eKeyCode::S) || Input::KeyD(eKeyCode::S))
		//{
		//MovePos.y -= 0.5 * Time::DeltaTime();
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
		//constantBuffer->Bind(eShaderStage::VS);
	}

	void Release()
	{
		delete mesh;
		delete shader;
		delete constantBuffer;
	}
}