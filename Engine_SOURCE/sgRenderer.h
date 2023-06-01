#pragma once
#include "LuruEngine.h"
#include "sgGraphicDevice_Dx11.h"

using namespace sg::math;
namespace sg::renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};


	extern Vertex vertexes[];
	extern Vertex square[];
	extern Vertex star[];

	extern ID3D11InputLayout* triangleLayout;
	extern ID3D11Buffer* triangleBuffer;
	extern ID3D11Buffer* triangleConstantBuffer;
	extern ID3DBlob* errorBlob;
	extern ID3DBlob* triangleVSBlob;
	extern ID3D11VertexShader* triangleVSShader;
	extern ID3DBlob* trianglePSBlob;
	extern ID3D11PixelShader* trianglePSShader;
	extern ID3D11Buffer* triangleIdxBuffer;

	extern ID3D11Buffer* squareBuffer;
	extern ID3D11Buffer* squareIdxBuffer;

	extern ID3D11Buffer* starBuffer;
	extern ID3D11Buffer* starIdxBuffer;

	extern Vector4 trianglePos;



	void Initialize();
	void Update();

}