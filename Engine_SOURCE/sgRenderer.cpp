#include "sgRenderer.h"

namespace sg::renderer
{

	Vertex vertexes[3] = {};

	Vertex square[4] = {};

	Vertex star[10] = {};

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
	// Input Layout (정점 정보)
	ID3D11InputLayout* polyLayout = nullptr;

	// Vertex Buffer
	ID3D11Buffer* polyBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;

	// error blob
	//ID3DBlob* errorBlob = nullptr;

	// Vertex Shader code -> Binary code
	ID3DBlob* polyVSBlob = nullptr;

	// Vertex Shader
	ID3D11VertexShader* polyVSShader = nullptr;

	// Pixel Shader coede -> Binary code
	ID3DBlob* polyPSBlob = nullptr;

	// Pixel Shader
	ID3D11PixelShader* polyPSShader = nullptr;



	void SetupState()
	{

	}
	
	void LoadBuffer()
	{
		D3D11_BUFFER_DESC triangleDesc = {};
		triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		triangleDesc.ByteWidth = sizeof(Vertex) * 3;
		//triangleDesc.ByteWidth = sizeof(Vertex) * 10;
		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA triangleData = {};
		triangleData.pSysMem = vertexes;
		//triangleData.pSysMem = square;
		sg::graphics::GetDevice()->CreateBuffer(&triangleBuffer, &triangleDesc, &triangleData);
	}

	// 성경이 만든것
	void LoadBuffer(int polynum, Vertex* poly, int* index)
	{
		D3D11_BUFFER_DESC polyDesc = {};
		polyDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		polyDesc.ByteWidth = sizeof(Vertex) * polynum;
		polyDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		polyDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA polyData = {};
		polyData.pSysMem = poly;
		sg::graphics::GetDevice()->CreateBuffer(&polyBuffer, &polyDesc, &polyData);


		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(int) * ((polynum - 2) * 3);
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		D3D11_SUBRESOURCE_DATA indexBufferData = {};
		indexBufferData.pSysMem = index;
		sg::graphics::GetDevice()->CreateBuffer(&indexBuffer, &indexBufferDesc, &indexBufferData);

	}
	
	void LoadShader()
	{
		sg::graphics::GetDevice()->CreateShader();
	}

	// 성경이만든것
	void LoadShader(int polynum)
	{
		sg::graphics::GetDevice()->CreateShader(polynum);
	}

	void Initialize()
	{
		//vertexes[0].pos = Vector3(0.0f, 0.5f, 0.0f);
		//vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		//vertexes[1].pos = Vector3(0.5f, -0.5f, 0.0f);
		//vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		//vertexes[2].pos = Vector3(-0.5f, -0.5f, 0.0f);
		//vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		square[0].pos = Vector3(0.2f, 0.8f, 0.0f);
		square[0].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		square[1].pos = Vector3(0.8f, 0.8f, 0.0f);
		square[1].color = Vector4(0.0f, 1.0f, 1.0f, 1.0f);
		square[2].pos = Vector3(0.8f, 0.2f, 0.0f);
		square[2].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		square[3].pos = Vector3(0.2f, 0.2f, 0.0f);
		square[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		int squareindex[6] = { 0, 1, 2, 0, 2, 3 };

		SetupState();
		LoadBuffer(4, square, squareindex);
		LoadShader(4);


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

		int starindex[24] = { 0,1,9,1,2,3,3,4,5,5,6,7,7,8,9,1,3,5,1,5,7,1,7,9};

		//SetupState();
		LoadBuffer(10, star, starindex);
		LoadShader(10);


	}
}