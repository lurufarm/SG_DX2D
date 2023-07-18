#pragma once
#include "LuruEngine.h"
#include "sgGraphicDevice_Dx11.h"
#include "sgMesh.h"
#include "sgShader.h"
#include "sgConstantBuffer.h"
#include "sgCamera.h"

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

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix mWorld;
		Matrix mView;
		Matrix mProjection;
	};
	CBUFFER(TimeCB, CBSLOT_TIME)
	{
		Vector4 mTime;
	};
	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 CameraPosition;
		Vector2 CameraScale;
		Vector2 Resolution;
	};
	CBUFFER(CollidingCB, CBSLOT_COLLIDING)
	{
		int ColliderColor;
		int none0;
		int none1;
		int none2;
	};


	extern sg::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End];

	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];
	
	extern sg::Camera* mainCamera;
	extern std::vector<sg::Camera*> cameras;
	extern std::vector<DebugMesh> debugMeshs;

	void Initialize();
	void Update();
	void Render();
	void Release();

	void PushDebugMeshAttribute(DebugMesh& mesh);

}