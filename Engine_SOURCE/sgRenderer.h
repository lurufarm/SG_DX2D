#pragma once
#include "LuruEngine.h"
#include "sgGraphicDevice_Dx11.h"
#include "sgMesh.h"
#include "sgShader.h"
#include "sgConstantBuffer.h"

using namespace sg::math;
using namespace sg::graphics;
namespace renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
		Vector2 uv;
	};


	extern Vertex vertexes[];
	extern sg::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End];

	void Initialize();
	void Update();
	void Release();

}