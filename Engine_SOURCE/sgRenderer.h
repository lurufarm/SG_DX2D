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
	extern Vertex star1[];

	extern ID3D11InputLayout* triangleLayout;
	extern ID3D11Buffer* triangleBuffer;
	extern ID3DBlob* errorBlob;
	extern ID3DBlob* triangleVSBlob;
	extern ID3D11VertexShader* triangleVSShader;
	extern ID3DBlob* trianglePSBlob;
	extern ID3D11PixelShader* trianglePSShader;

	extern ID3D11InputLayout* polyLayout;
	extern ID3D11Buffer* polyBuffer;
	extern ID3DBlob* polyVSBlob;
	extern ID3D11VertexShader* polyVSShader;
	extern ID3DBlob* polyPSBlob;
	extern ID3D11PixelShader* polyPSShader;

	extern ID3D11Buffer* indexBuffer;


	void Initialize();

}