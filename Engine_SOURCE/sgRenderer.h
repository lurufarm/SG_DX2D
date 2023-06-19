#pragma once
#include "LuruEngine.h"
#include "sgGraphicDevice_Dx11.h"
#include "sgMesh.h"
#include "sgShader.h"
#include "sgConstantBuffer.h"

using namespace sg::math;
namespace renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
		Vector2 uv;
	};


	extern Vertex vertexes[];
	//extern Vertex square[];
	//extern Vertex star[];

	extern sg::Mesh* mesh;
	extern sg::Shader* shader;
	extern sg::graphics::ConstantBuffer* constantBuffer;

	//extern Vector4 MovePos;

	void Initialize();
	void Update();
	void Release();

}