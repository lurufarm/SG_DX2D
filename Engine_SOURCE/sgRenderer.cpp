#include "sgRenderer.h"
#include "sgInput.h"
#include "sgTime.h"

namespace sg::renderer
{

	Vertex vertexes[3] = {};
	Vertex square[4] = {};
	Vertex star[10] = {};


	// Input Layout (정점 정보)
	ID3D11InputLayout* triangleLayout = nullptr;
	
	// Vertex Buffer
	ID3D11Buffer* triangleBuffer = nullptr;
	ID3D11Buffer* triangleIdxBuffer = nullptr;
	ID3D11Buffer* triangleConstantBuffer = nullptr;

	// error blob
	ID3DBlob* errorBlob = nullptr;

	// Vertex Shader code -> Binary code
	ID3DBlob* triangleVSBlob = nullptr;

	// Vertex Shader
	ID3D11VertexShader* triangleVSShader = nullptr;

	// Pixel Shader coede -> Binary code
	ID3DBlob* trianglePSBlob = nullptr;

	// Pixel Shader
	ID3D11PixelShader* trianglePSShader = nullptr;

	//ID3D11InputLayout* myLayout = nullptr;
	ID3D11Buffer* squareBuffer = nullptr;
	ID3D11Buffer* squareIdxBuffer = nullptr;

	ID3D11Buffer* starBuffer = nullptr;
	ID3D11Buffer* starIdxBuffer = nullptr;

	Vector4 trianglePos = { 0.0f, 0.0f, 0.0f, 1.0f };

	void SetupState()
	{

	}
	
	void LoadBuffer() // triangle
	{
		D3D11_BUFFER_DESC triangleDesc = {};
		triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		triangleDesc.ByteWidth = sizeof(Vertex) * 3;
		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA triangleData = {};
		triangleData.pSysMem = vertexes;
		sg::graphics::GetDevice()->CreateBuffer(&triangleBuffer, &triangleDesc, &triangleData);

		std::vector<UINT> indexes = {};
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		// 인덱스 버퍼 설정
		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.ByteWidth = sizeof(int) * 3;
		indexBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		indexBufferDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA indexBufferData = {};
		indexBufferData.pSysMem = indexes.data();
		sg::graphics::GetDevice()->CreateBuffer(&triangleIdxBuffer, &indexBufferDesc, &indexBufferData);

		// 상수 버퍼 설정
		D3D11_BUFFER_DESC constantBufferDesc = {};
		constantBufferDesc.ByteWidth = sizeof(Vector4);
		constantBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		sg::graphics::GetDevice()->CreateBuffer(&triangleConstantBuffer, &constantBufferDesc, nullptr);

		//Vector4 pos(-0.5f, 0.0f, 0.0f, 1.0f);
		sg::graphics::GetDevice()->SetConstantBuffer(triangleConstantBuffer, &trianglePos, sizeof(Vector4));
		sg::graphics::GetDevice()->BindConstantBuffer(eShaderStage::VS, eCBType::Transform, triangleConstantBuffer);

	}

	void LoadBuffer(int vertexesnum, std::vector<UINT> idx, Vertex* poly, ID3D11Buffer** buffer, ID3D11Buffer** IdxBuffer)
	{
		// 버텍스 버퍼 설정
		D3D11_BUFFER_DESC polyDesc = {};
		polyDesc.ByteWidth = sizeof(Vertex) * vertexesnum;
		polyDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		polyDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		polyDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA polyData = {};
		polyData.pSysMem = poly;
		sg::graphics::GetDevice()->CreateBuffer(buffer, &polyDesc, &polyData);


		//std::vector<UINT> indexes = {};
		//indexes.push_back(0);
		//indexes.push_back(1);
		//indexes.push_back(2);
	
		// 인덱스 버퍼 설정
		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.ByteWidth = sizeof(int) * idx.size();
		indexBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		indexBufferDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA indexBufferData = {};
		indexBufferData.pSysMem = idx.data();
		sg::graphics::GetDevice()->CreateBuffer(IdxBuffer, &indexBufferDesc, &indexBufferData);

		// 상수 버퍼 설정
		D3D11_BUFFER_DESC constantBufferDesc = {};
		constantBufferDesc.ByteWidth = sizeof(Vector4);
		constantBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		sg::graphics::GetDevice()->CreateBuffer(&triangleConstantBuffer, &constantBufferDesc, nullptr);
		
		//Vector4 pos(0.0f, 0.0f, 0.0f, 1.0f);

		sg::graphics::GetDevice()->SetConstantBuffer(triangleConstantBuffer, &trianglePos, sizeof(Vector4));
		sg::graphics::GetDevice()->BindConstantBuffer(eShaderStage::VS, eCBType::Transform, triangleConstantBuffer);

	}
	
	void LoadShader()
	{
		sg::graphics::GetDevice()->CreateShader();
	}

	void Initialize()
	{
		vertexes[0].pos = Vector3(0.0f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[1].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[2].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		trianglePos = { 0.0f, 0.0f, 0.0f, 1.0f };

		square[0].pos = Vector3(0.2f, 0.8f, 0.0f);
		square[0].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		square[1].pos = Vector3(0.8f, 0.8f, 0.0f);
		square[1].color = Vector4(0.0f, 1.0f, 1.0f, 1.0f);
		square[2].pos = Vector3(0.8f, 0.2f, 0.0f);
		square[2].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		square[3].pos = Vector3(0.2f, 0.2f, 0.0f);
		square[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		star[0].pos = Vector3(-0.5f, 0.8f, 0.0f);
		star[0].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		star[1].pos = Vector3(-0.4f, 0.6f, 0.0f);
		star[1].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		star[2].pos = Vector3(-0.2f, 0.5f, 0.0f);
		star[2].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		star[3].pos = Vector3(-0.3f, 0.35f, 0.0f);
		star[3].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		star[4].pos = Vector3(-0.3f, 0.1f, 0.0f);
		star[4].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		star[5].pos = Vector3(-0.5, 0.2f, 0.0f);
		star[5].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		star[6].pos = Vector3(-0.7f, 0.1f, 0.0f);
		star[6].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		star[7].pos = Vector3(-0.7f, 0.35f, 0.0f);
		star[7].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		star[8].pos = Vector3(-0.8f, 0.5f, 0.0f);
		star[8].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		star[9].pos = Vector3(-0.6f, 0.6f, 0.0f);
		star[9].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);

		std::vector<UINT>squareidx = { 0, 1, 2, 0, 2, 3};
		std::vector<UINT>staridx = { 0, 1, 9, 1, 2, 3, 3, 4, 5, 5, 6, 7, 7, 8, 9, 1, 3, 5, 1, 5, 7, 1, 7, 9};

		
		LoadShader();
		LoadBuffer();
		LoadBuffer(4, squareidx, square, &squareBuffer, &squareIdxBuffer);
		LoadBuffer(10, staridx, star, &starBuffer, &starIdxBuffer);


	}
	void Update()
	{
		if (Input::KeyP(eKeyCode::W) || Input::KeyD(eKeyCode::W))
		{
			trianglePos.y += 0.5 * Time::DeltaTime();
		}
		else if (Input::KeyP(eKeyCode::S) || Input::KeyD(eKeyCode::S))
		{
			trianglePos.y -= 0.5 * Time::DeltaTime();
		}
		if (Input::KeyP(eKeyCode::A) || Input::KeyD(eKeyCode::A))
		{
			trianglePos.x -= 0.5 * Time::DeltaTime();
		}
		else if (Input::KeyP(eKeyCode::D) || Input::KeyD(eKeyCode::D))
		{
			trianglePos.x += 0.5 * Time::DeltaTime();
		}
		//LoadBuffer();
		sg::graphics::GetDevice()->SetConstantBuffer(triangleConstantBuffer, &trianglePos, sizeof(Vector4));
		sg::graphics::GetDevice()->BindConstantBuffer(eShaderStage::VS, eCBType::Transform, triangleConstantBuffer);

	}
}