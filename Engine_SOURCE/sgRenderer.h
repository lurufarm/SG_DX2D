#pragma once
#include "LuruEngine.h"
#include "sgGraphicDevice_Dx11.h"
#include "sgMesh.h"
#include "sgShader.h"
#include "sgConstantBuffer.h"
#include "sgStructuredBuffer.h"
#include "sgCamera.h"
#include "sgLight.h"

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
	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 CameraPosition;
		Vector2 CameraScale;
		Vector2 Resolution;
	};

	CBUFFER(AnimatorCB, CBSLOT_ANIMATION2D)
	{
		Vector2 spriteLeftTop;
		Vector2 spriteSize;
		Vector2 spriteOffset;
		Vector2 atlasSize;
		UINT animationType;
		Vector3 dummydata;
	};

	CBUFFER(MyCB, CBSLOT_MYCB)
	{
		int ColliderColor;
		int TileIndex;
		int none1;
		int none2;
	};

	CBUFFER(TimeCB, CBSLOT_TIME)
	{
		Vector4 mTime;
	};

	CBUFFER(TransparentCB, CBSLOT_TPCB)
	{
		int alphaValue;
		Vector3 pad;
	};

	CBUFFER(HPBarCB, CBSLOT_HPCB)
	{
		float maxHP;
		float curHP;
		Vector2 padHP;
	};

	CBUFFER(ParticleCB, CBSLOT_PARTICLE)
	{
		float elapsedTime;
		float deltaTime;

		// Count
		UINT particleCount;
		int ParticlePad;
	};

	CBUFFER(NoiseCB, CBSLOT_NOISE)
	{
		Vector4 size;
	};

	extern sg::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End];

	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];
	
	// Light
	extern sg::graphics::StructuredBuffer* lightsBuffer;
	extern std::vector<sg::Light*> lights;

	extern sg::Camera* mainCamera;
	extern std::vector<sg::Camera*> cameras;
	extern std::vector<DebugMesh> debugMeshs;

	void Initialize();
	void BindLights();
	void Render();
	void Release();

	void PushDebugMeshAttribute(DebugMesh& mesh);

	extern sg::GameObject* light;
	extern float mTime;

}