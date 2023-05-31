#include "sgRenderer.h"

namespace sg::renderer
{

	Vertex vertexes[3] = {};


	// Input Layout (정점 정보)
	ID3D11InputLayout* triangleLayout = nullptr;
	
	// Vertex Buffer
	ID3D11Buffer* triangleBuffer = nullptr;

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

	// ----
	ID3D11InputLayout* polyLayout = nullptr;
	ID3D11Buffer* polyBuffer = nullptr;
	ID3DBlob* polyVSBlob = nullptr;
	ID3D11VertexShader* polyVSShader = nullptr;
	ID3DBlob* polyPSBlob = nullptr;
	ID3D11PixelShader* polyPSShader = nullptr;
	ID3D11Buffer* polyindexBuffer = nullptr;


	ID3D11InputLayout* myLayout = nullptr;
	ID3D11Buffer* myBuffer = nullptr;
	ID3D11Buffer* myindexBuffer = nullptr;

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
	}

	// 성경이 만든것
	void LoadBuffer(int vertexesnum, int indexnum, Vertex* poly, int* index, ID3D11Buffer** buffer, ID3D11Buffer** indexbuffer)
	{
		D3D11_BUFFER_DESC polyDesc = {};
		polyDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		polyDesc.ByteWidth = sizeof(Vertex) * vertexesnum;
		polyDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		polyDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA polyData = {};
		polyData.pSysMem = poly;
		sg::graphics::GetDevice()->CreateBuffer(buffer, &polyDesc, &polyData);


		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(int) * indexnum;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		D3D11_SUBRESOURCE_DATA indexBufferData = {};
		indexBufferData.pSysMem = index;
		sg::graphics::GetDevice()->CreateBuffer(indexbuffer, &indexBufferDesc, &indexBufferData);

	}
	
	void LoadShader()
	{
		sg::graphics::GetDevice()->CreateShader();
	}

	void Initialize()
	{
		//vertexes[0].pos = Vector3(0.0f, 0.5f, 0.0f);
		//vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		//vertexes[1].pos = Vector3(0.5f, -0.5f, 0.0f);
		//vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		//vertexes[2].pos = Vector3(-0.5f, -0.5f, 0.0f);
		//vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		vertexes[0].pos = Vector3(0.2f, 0.8f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexes[1].pos = Vector3(0.8f, 0.8f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 1.0f, 1.0f);
		vertexes[2].pos = Vector3(0.8f, 0.2f, 0.0f);
		vertexes[2].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		vertexes[3].pos = Vector3(0.2f, 0.2f, 0.0f);
		vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		vertexes[4].pos = Vector3(-0.5f, 0.8f, 0.0f);
		vertexes[4].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		vertexes[5].pos = Vector3(-0.4f, 0.6f, 0.0f);
		vertexes[5].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		vertexes[6].pos = Vector3(-0.2f, 0.5f, 0.0f);
		vertexes[6].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		vertexes[7].pos = Vector3(-0.3f, 0.35f, 0.0f);
		vertexes[7].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		vertexes[8].pos = Vector3(-0.3f, 0.1f, 0.0f);
		vertexes[8].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		vertexes[9].pos = Vector3(-0.5, 0.2f, 0.0f);
		vertexes[9].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		vertexes[10].pos = Vector3(-0.7f, 0.1f, 0.0f);
		vertexes[10].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		vertexes[11].pos = Vector3(-0.7f, 0.35f, 0.0f);
		vertexes[11].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		vertexes[12].pos = Vector3(-0.8f, 0.5f, 0.0f);
		vertexes[12].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		vertexes[13].pos = Vector3(-0.6f, 0.6f, 0.0f);
		vertexes[13].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);

		int myindex[30] = { 0, 1, 2, 0, 2, 3, 4, 5, 13, 5, 6, 7, 7, 8, 9, 9, 10, 11, 11, 12, 13, 5, 7, 9, 5, 9, 11, 5, 11, 13 };
		//int myindex[6] = { 0, 1, 2, 0, 2, 3};

		LoadShader();
		//LoadBuffer();
		LoadBuffer(14, 30, vertexes, myindex, & myBuffer, & myindexBuffer);


	}
}