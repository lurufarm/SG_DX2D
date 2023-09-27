#include "sgRenderer.h"
#include "sgResources.h"
#include "sgTexture.h"
#include "sgMaterial.h"
#include "sgPaintShader.h"
#include "sgStructuredBuffer.h"
#include "sgParticleShader.h"

namespace renderer
{
	using namespace sg;
	using namespace sg::graphics;

	sg::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End] = {};

	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::End] = {};

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};
	
	// light
	std::vector<Light*> lights = {};
	StructuredBuffer* lightsBuffer = nullptr;

	//
	sg::Camera* mainCamera = nullptr;
	std::vector<sg::Camera*> cameras = {};
	std::vector<DebugMesh> debugMeshs = {};

	void SetupState()
	{
#pragma region Input Layout
		// Input Layout 정점 구조를 정보를 넘겨준다.
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {};

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

		arrLayout[2].AlignedByteOffset = 28;
		arrLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayout[2].InputSlot = 0;
		arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[2].SemanticName = "TEXCOORD";
		arrLayout[2].SemanticIndex = 0;

		std::shared_ptr<Shader> shader = sg::Resources::Find<Shader>(L"TriangleShader");
		sg::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = sg::Resources::Find<Shader>(L"SpriteShader");
		sg::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = sg::Resources::Find<Shader>(L"SpriteAniShader");
		sg::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = sg::Resources::Find<Shader>(L"SpriteAniShader2");
		sg::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = sg::Resources::Find<Shader>(L"GridShader");
		sg::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = sg::Resources::Find<Shader>(L"DebugShader");
		sg::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = sg::Resources::Find<Shader>(L"ParticleShader");
		sg::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());
		
		shader = sg::Resources::Find<Shader>(L"CatPatternShader");
		sg::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = sg::Resources::Find<Shader>(L"lobby_spaceShader1");
		sg::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = sg::Resources::Find<Shader>(L"lobby_spaceShader2");
		sg::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = sg::Resources::Find<Shader>(L"TileShader");
		sg::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = sg::Resources::Find<Shader>(L"HPBarShader");
		sg::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

#pragma endregion
#pragma region Sampler State
		// Sampler State
		D3D11_SAMPLER_DESC pdesc = {};
		pdesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		pdesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		pdesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		pdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		GetDevice()->CreateSamplerState(&pdesc, samplerState[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 0, samplerState[(UINT)eSamplerType::Point].GetAddressOf());

		D3D11_SAMPLER_DESC adesc = {};
		adesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		adesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		adesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		adesc.MaxAnisotropy = 4;
		adesc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState(&adesc, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 1, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion
#pragma region Rasterizer State
		D3D11_RASTERIZER_DESC rasterizerDesc = {};
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		GetDevice()->CreateRasterizerState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
		GetDevice()->CreateRasterizerState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizerState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizerState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());
#pragma endregion
#pragma region Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};

		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::Less].GetAddressOf());
		
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::Greater].GetAddressOf());

		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		depthStencilDesc.DepthEnable = false;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::None].GetAddressOf());
#pragma endregion
#pragma region Blend State
		D3D11_BLEND_DESC blendDesc = {};
		blendStates[(UINT)eBSType::Default] = nullptr;

		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		GetDevice()->CreateBlendState(&blendDesc
			, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		GetDevice()->CreateBlendState(&blendDesc
			, blendStates[(UINT)eBSType::OneOne].GetAddressOf());

#pragma endregion
	}
	
	void LoadMesh()
	{
		std::vector<Vertex> vertexes = {};
		std::vector<UINT> indexes = {};
		std::vector<Vertex> pointvertexes = {};
		std::vector<UINT> pointindexes = {};

		//PointMesh
		Vertex v = {};
		v.pos = Vector3(0.0f, 0.0f, 0.0f);
		pointvertexes.push_back(v);
		pointindexes.push_back(0);
		std::shared_ptr<Mesh> pointmesh = std::make_shared<Mesh>();
		pointmesh->CreateVertexBuffer(pointvertexes.data(), pointvertexes.size());
		pointmesh->CreateIndexBuffer(pointindexes.data(), pointindexes.size());
		Resources::Insert(L"PointMesh", pointmesh);

		// RECT
		vertexes.resize(4);
		vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		// Vertex Buffer 설정
		std::shared_ptr<Mesh>mesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", mesh);
		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size());


		// Index Buffer 설정
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());




#pragma region Debug Mesh
		// Rect Debug Mesh
		std::shared_ptr<Mesh> rectDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugRect", rectDebug);
		rectDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		rectDebug->CreateIndexBuffer(indexes.data(), indexes.size());

		// Circle Debug Mesh
		vertexes.clear();
		indexes.clear();

		Vertex center = {};
		center.pos = Vector3(0.0f, 0.0f, 0.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes.push_back(center);

		int iSlice = 40;
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;

		for (int i = 0; i < iSlice; ++i)
		{
			center.pos = Vector3(fRadius * cosf(fTheta * (float)i)
				, fRadius * sinf(fTheta * (float)i)
				, 0.0f);
			center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
			vertexes.push_back(center);
		}
		
		for (int i= 0 ; i< vertexes.size() - 2 ; ++i)
		{
			indexes.push_back(i + 1);
		}
		indexes.push_back(1);
		std::shared_ptr<Mesh> circleDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugCircle", circleDebug);
		circleDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		circleDebug->CreateIndexBuffer(indexes.data(), indexes.size());
#pragma endregion



	}

	void LoadBuffer()
	{

		// Transform
		constantBuffer[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		// Grid
		constantBuffer[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffer[(UINT)eCBType::Grid]->Create(sizeof(GridCB));
	
		// Animator
		constantBuffer[(UINT)eCBType::Animator] = new ConstantBuffer(eCBType::Animator);
		constantBuffer[(UINT)eCBType::Animator]->Create(sizeof(AnimatorCB));

		// MyCBType
		constantBuffer[(UINT)eCBType::MyCBType] = new ConstantBuffer(eCBType::MyCBType);
		constantBuffer[(UINT)eCBType::MyCBType]->Create(sizeof(MyCB));

		// Time
		constantBuffer[(UINT)eCBType::Time] = new ConstantBuffer(eCBType::Time);
		constantBuffer[(UINT)eCBType::Time]->Create(sizeof(TimeCB));

		// Transparent
		constantBuffer[(UINT)eCBType::Transparent] = new ConstantBuffer(eCBType::Transparent);
		constantBuffer[(UINT)eCBType::Transparent]->Create(sizeof(TransparentCB));

		// HPBar
		constantBuffer[(UINT)eCBType::HPBar] = new ConstantBuffer(eCBType::HPBar);
		constantBuffer[(UINT)eCBType::HPBar]->Create(sizeof(HPBarCB));

		// Particle
		constantBuffer[(UINT)eCBType::Particle] = new ConstantBuffer(eCBType::Particle);
		constantBuffer[(UINT)eCBType::Particle]->Create(sizeof(ParticleCB));

		// Noise

		constantBuffer[(UINT)eCBType::Noise] = new ConstantBuffer(eCBType::Particle);
		constantBuffer[(UINT)eCBType::Noise]->Create(sizeof(NoiseCB));


		// light structured buffer
		lightsBuffer = new StructuredBuffer();
		lightsBuffer->Create(sizeof(LightAttribute), 100, eViewType::SRV, nullptr, true);		
	}
	
	void LoadTexture()
	{
		// paint texture
		std::shared_ptr<Texture> uavTexture = std::make_shared<Texture>();
		uavTexture->Create(1024, 1024, DXGI_FORMAT_B8G8R8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
		sg::Resources::Insert(L"PaintTexture", uavTexture);

		std::shared_ptr<Texture> particle = Resources::Load<Texture>(L"particleCircle", L"..\\Resources\\Particle\\HardCircle.png");
		sg::Resources::Insert(L"particletest", particle);

		std::shared_ptr<Texture> noise01 = Resources::Load<Texture>(L"Noise01", L"..\\Resources\\Particle\\noise_01.png");
		std::shared_ptr<Texture> noise02 = Resources::Load<Texture>(L"Noise02", L"..\\Resources\\Particle\\noise_02.png");
		std::shared_ptr<Texture> noise03 = Resources::Load<Texture>(L"Noise03", L"..\\Resources\\Particle\\noise_03.jpg");
		sg::Resources::Insert(L"Noise01", noise01);
		sg::Resources::Insert(L"Noise02", noise02);
		sg::Resources::Insert(L"Noise03", noise03);

	}

	void LoadShader()
	{
		std::shared_ptr<Shader>shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
		sg::Resources::Insert(L"TriangleShader", shader);

		std::shared_ptr<Shader> spriteShader = std::make_shared<Shader>();
		spriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		spriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		sg::Resources::Insert(L"SpriteShader", spriteShader);

		std::shared_ptr<Shader> spriteAniShader = std::make_shared<Shader>();
		spriteAniShader->Create(eShaderStage::VS, L"SpriteAnimationVS.hlsl", "main");
		spriteAniShader->Create(eShaderStage::PS, L"SpriteAnimationPS.hlsl", "main");
		sg::Resources::Insert(L"SpriteAniShader", spriteAniShader);

		std::shared_ptr<Shader> spriteAniShader2 = std::make_shared<Shader>();
		spriteAniShader2->Create(eShaderStage::VS, L"SpriteAnimationVS.hlsl", "main");
		spriteAniShader2->Create(eShaderStage::PS, L"SpriteAnimationPS.hlsl", "main2");
		sg::Resources::Insert(L"SpriteAniShader2", spriteAniShader2);

		std::shared_ptr<Shader> gridShader = std::make_shared<Shader>();
		gridShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		gridShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		sg::Resources::Insert(L"GridShader", gridShader);

		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		debugShader->SetRSState(eRSType::WireframeNone);
		sg::Resources::Insert(L"DebugShader", debugShader);

		std::shared_ptr<PaintShader> paintShader = std::make_shared<PaintShader>();
		paintShader->Create(L"PaintCS.hlsl", "main");
		sg::Resources::Insert(L"PaintShader", paintShader);

		std::shared_ptr<ParticleShader> psSystemShader = std::make_shared<ParticleShader>();
		psSystemShader->Create(L"ParticleCS.hlsl", "main");
		sg::Resources::Insert(L"ParticleSystemShader", psSystemShader);

		std::shared_ptr<Shader> particleShader = std::make_shared<Shader>();
		particleShader->Create(eShaderStage::VS, L"ParticleVS.hlsl", "main");
		particleShader->Create(eShaderStage::GS, L"ParticleGS.hlsl", "main");
		particleShader->Create(eShaderStage::PS, L"ParticlePS.hlsl", "main");
		particleShader->SetRSState(eRSType::SolidNone);
		particleShader->SetDSState(eDSType::NoWrite);
		particleShader->SetBSState(eBSType::AlphaBlend);
		particleShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
		sg::Resources::Insert(L"ParticleShader", particleShader);


		// 이하로 직접 만든거

		std::shared_ptr<Shader> catPatternShader = std::make_shared<Shader>();
		catPatternShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		catPatternShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "Select_catpattern");
		sg::Resources::Insert(L"CatPatternShader", catPatternShader);

		std::shared_ptr<Shader> SpaceShader1 = std::make_shared<Shader>();
		SpaceShader1->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		SpaceShader1->Create(eShaderStage::PS, L"SpritePS.hlsl", "lobby_space1");
		sg::Resources::Insert(L"lobby_spaceShader1", SpaceShader1);

		std::shared_ptr<Shader> SpaceShader2 = std::make_shared<Shader>();
		SpaceShader2->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		SpaceShader2->Create(eShaderStage::PS, L"SpritePS.hlsl", "lobby_space2");
		sg::Resources::Insert(L"lobby_spaceShader2", SpaceShader2);

		std::shared_ptr<Shader> TileShader = std::make_shared<Shader>();
		TileShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		TileShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "Tile");
		sg::Resources::Insert(L"TileShader", TileShader);

		std::shared_ptr<Shader> HPBarShader = std::make_shared<Shader>();
		HPBarShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		HPBarShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "HPBar");
		sg::Resources::Insert(L"HPBarShader", HPBarShader);



	}

	void LoadMaterial()
	{
#pragma region Find Shader
		std::shared_ptr<Shader> shader
			= Resources::Find<Shader>(L"SpriteShader");

		std::shared_ptr<Shader>gridShader
			= Resources::Find<Shader>(L"GridShader");

		std::shared_ptr<Shader>debugShader
			= Resources::Find<Shader>(L"DebugShader");

		std::shared_ptr<Shader> AniShader
			= Resources::Find<Shader>(L"SpriteAniShader");

		std::shared_ptr<Shader> AniShader2
			= Resources::Find<Shader>(L"SpriteAniShader2");

		std::shared_ptr<Shader> SelectSceneShader
			= Resources::Find<Shader>(L"CatPatternShader");

		std::shared_ptr<Shader> LobbySpaceShader1
			= Resources::Find<Shader>(L"lobby_spaceShader1");

		std::shared_ptr<Shader> LobbySpaceShader2
			= Resources::Find<Shader>(L"lobby_spaceShader2");

		std::shared_ptr<Shader> TileShader
			= Resources::Find<Shader>(L"TileShader");

		std::shared_ptr<Shader> HPBarShader
			= Resources::Find<Shader>(L"HPBarShader");

		std::shared_ptr<Shader> ParticleShader
			= Resources::Find<Shader>(L"ParticleShader");


#pragma endregion
#pragma region Basic Texture and Basic Material declaration 
		std::shared_ptr<Texture> texture;
		std::shared_ptr<Material> material;

		std::shared_ptr<Texture> particleTexx2 = Resources::Find<Texture>(L"particletest");
		std::shared_ptr<Material> particlematerial = std::make_shared<Material>();
		particlematerial->SetShader(ParticleShader);
		particlematerial->SetTexture(particleTexx2);
		particlematerial->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"ParticleMaterial2", particlematerial);

		// Test
		//texture	= Resources::Load<Texture>(L"Cat", L"..\\Resources\\Texture\\Cat.png");
		//material = std::make_shared<Material>();
		//material->SetShader(TileShader);
		//material->SetTexture(texture);
		//material->SetRendereringMode(eRenderingMode::CutOut);
		//Resources::Insert(L"SpriteMaterial", material);

		// PaintMaterial
		texture = Resources::Find<Texture>(L"PaintTexture");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"PaintMaterial", material);

		// particle Material
		
		//material = std::make_shared<Material>();
		//material->SetShader(ParticleShader);
		//material->SetRendereringMode(eRenderingMode::Transparent);
		//Resources::Insert(L"ParticleMaterial", material);

		// Tile
		texture = Resources::Load<Texture>(L"TilePalette", L"..\\Resources\\Tile\\tilepalette.bmp");
		material = std::make_shared<Material>();
		material->SetShader(TileShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Opaque);
		Resources::Insert(L"TilePaletteMaterial", material);

		// Grid
		material = std::make_shared<Material>();
		material->SetShader(gridShader);
		Resources::Insert(L"GridMaterial", material);

		// Debug
		material = std::make_shared<Material>();
		material->SetShader(debugShader);
		Resources::Insert(L"DebugMaterial", material);

		// Animation
		material = std::make_shared<Material>();
		material->SetShader(AniShader);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"AnimationMaterial", material);

		// Animation2
		material = std::make_shared<Material>();
		material->SetShader(AniShader2);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"AnimationMaterial2", material);



#pragma endregion
#pragma region UI Material
		 // UI_Exit Button
		texture = Resources::Load<Texture>(L"ExitButton", L"..\\Resources\\UI\\NavButton_12.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"UIExitButton", material);
		
		 // UI_SelectBox 0 (top left)
		texture = Resources::Load<Texture>(L"UI_SelectBox_tl", L"..\\Resources\\UI\\selectbox_tl.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"UISBox_tl", material);
		
		 // UI_SelectBox 1 (top right)
		texture = Resources::Load<Texture>(L"UI_SelectBox_tr", L"..\\Resources\\UI\\selectbox_tr.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"UISBox_tr", material);
		
		 // UI_SelectBox 2 (bottom left)
		texture = Resources::Load<Texture>(L"UI_SelectBox_bl", L"..\\Resources\\UI\\selectbox_bl.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"UISBox_bl", material);
		
		 // UI_SelectBox 3 (bottom right)
		texture = Resources::Load<Texture>(L"UI_SelectBox_br", L"..\\Resources\\UI\\selectbox_br.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"UISBox_br", material);

		// UI_Coin
		texture = Resources::Load<Texture>(L"UI_Coin", L"..\\Resources\\UI\\UI_coin.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"UICoin", material);
		
		// UI_Option
		texture = Resources::Load<Texture>(L"UI_Option", L"..\\Resources\\UI\\UI_option.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"UIOption", material);

		// UI_Tokki
		texture = Resources::Load<Texture>(L"UI_Tokki", L"..\\Resources\\UI\\UI_tokki.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"UITokki", material);

		// UI_Plus
		texture = Resources::Load<Texture>(L"UI_Plus", L"..\\Resources\\UI\\UI_plus.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"UIPlus", material);

		// UI_I
		texture = Resources::Load<Texture>(L"UI_I", L"..\\Resources\\UI\\UI_I.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"UIIbutton", material);

		// UI_J
		texture = Resources::Load<Texture>(L"UI_J", L"..\\Resources\\UI\\UI_J.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"UIJbutton", material);

		// UI_K
		texture = Resources::Load<Texture>(L"UI_K", L"..\\Resources\\UI\\UI_K.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"UIKbutton", material);

		// UI_CharSelect
		texture = Resources::Load<Texture>(L"UI_CharSelect", L"..\\Resources\\UI\\characterselect.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Opaque);
		Resources::Insert(L"UICharSelect", material);

		// UI_HPBase
		texture = Resources::Load<Texture>(L"UI_HPBase", L"..\\Resources\\UI\\hp_base.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"UIHPBase", material);

		// UI_HPBar
		texture = Resources::Load<Texture>(L"UI_HPBar", L"..\\Resources\\UI\\hp_green.png");
		material = std::make_shared<Material>();
		material->SetShader(HPBarShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"UIHPBar", material);


#pragma endregion
#pragma region Title Scene Material

		 // BGImg
		texture = Resources::Load<Texture>(L"Title", L"..\\Resources\\Title\\title.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Opaque);
		Resources::Insert(L"ImgTitle01", material);
		
		 // TItle logo
		texture = Resources::Load<Texture>(L"Logo", L"..\\Resources\\Title\\Logo01.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"ImgLogo01", material);
		
#pragma endregion
#pragma region Select Scene Material
		 // Select - Story
		texture	= Resources::Load<Texture>(L"Story", L"..\\Resources\\Title\\ModeIllust_Story.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"ImgStory", material);

		texture = Resources::Load<Texture>(L"Story_text", L"..\\Resources\\Title\\Title_StoryMode.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"ImgStory_text", material);
		
		 // Select - Party
		texture = Resources::Load<Texture>(L"Party", L"..\\Resources\\Title\\ModeIllust_Party.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"ImgParty", material);

		texture = Resources::Load<Texture>(L"Party_text", L"..\\Resources\\Title\\Title_PartyMode.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"ImgParty_text", material);
		
		 // Select - CatPattern
		texture = Resources::Load<Texture>(L"CatPattern", L"..\\Resources\\Title\\CatPattern.png");
		material = std::make_shared<Material>();
		material->SetShader(SelectSceneShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"ImgCatPattern", material);

		// PlayScene - Starting Plate

		texture = Resources::Load<Texture>(L"Img_StartPlate", L"..\\Resources\\Map\\Common\\StartingPlate.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"ImgStartingPlate", material);

		// PlayScene - Reward Plates

		texture = Resources::Load<Texture>(L"Img_RewardPlate0", L"..\\Resources\\Map\\Common\\RewardPlate0.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"ImgRewardPlate0", material);

		texture = Resources::Load<Texture>(L"Img_RewardPlate1", L"..\\Resources\\Map\\Common\\RewardPlate1.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"ImgRewardPlate1", material);

		texture = Resources::Load<Texture>(L"Img_LevUp", L"..\\Resources\\UI\\LevelUp.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"ImgLevUp", material);

		texture = Resources::Load<Texture>(L"Img_Shadow", L"..\\Resources\\Effect\\shadow.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"ImgShadow", material);

#pragma endregion
#pragma region Lobby Scene Material
		 // Lobby - BG1
		texture = Resources::Load<Texture>(L"Space1", L"..\\Resources\\Lobby\\SvSpace.png");
		material = std::make_shared<Material>();
		material->SetShader(LobbySpaceShader1);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"ImgSpace1", material);
		
		 // Lobby - BG2
		texture	= Resources::Load<Texture>(L"Space2", L"..\\Resources\\Lobby\\SvSpace2.png");
		material = std::make_shared<Material>();
		material->SetShader(LobbySpaceShader2);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"ImgSpace2", material);
		
		 // Lobby_map
		texture = Resources::Load<Texture>(L"Lobby", L"..\\Resources\\Lobby\\Lobby.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"ImgLobbyMap", material);
		
		 // Lobby_Character
		texture = Resources::Load<Texture>(L"Lobby_Character", L"..\\Resources\\Lobby\\SurvivalCharacter_01.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"InteractableLobbyCharacter", material);

		
		 // Lobby_Upgrade
		texture = Resources::Load<Texture>(L"Lobby_Upgrade", L"..\\Resources\\Lobby\\SurvivalUpgrade_01.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"InteractableLobbyUpgrade", material);

		
		 // Lobby_Gate

		
		 // Lobby_Molding
		texture = Resources::Load<Texture>(L"Lobby_Molding", L"..\\Resources\\Lobby\\SvMolding.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"ImgMolding", material);

		// Lobby_CardBook
		texture = Resources::Load<Texture>(L"Lobby_CardBook", L"..\\Resources\\Lobby\\SurvivalCardBook.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"InteractableLobbyCardBook", material);

		
#pragma endregion
#pragma region Stage0_Forest

		// Stage0_ForestFd01 Map
		texture = Resources::Load<Texture>(L"Stage0_ForestFd01_Map", L"..\\Resources\\Map\\Stage0\\stage0_forestfd_1.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"Stage0ForestFd01_Map", material);

		// Stage0_ForestFd02 Map
		texture = Resources::Load<Texture>(L"Stage0_ForestFd02_Map", L"..\\Resources\\Map\\Stage0\\stage0_forestfd_2.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"Stage0ForestFd02_Map", material);
		
		// Stage0_ForestFd03 Map
		texture = Resources::Load<Texture>(L"Stage0_ForestFd03_Map", L"..\\Resources\\Map\\Stage0\\stage0_forestfd_3.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"Stage0ForestFd03_Map", material);

		// Stage0_ForestFd04 Map
		texture = Resources::Load<Texture>(L"Stage0_ForestFd04_Map", L"..\\Resources\\Map\\Stage0\\stage0_forestfd_4.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"Stage0ForestFd04_Map", material);

		// Stage0_ForestDg01 Map
		texture = Resources::Load<Texture>(L"Stage0_ForestDg01_Map", L"..\\Resources\\Map\\Stage0\\stage0_forestdg_1.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"Stage0ForestDg01_Map", material);

		// Stage0_ForestDg02 Map
		texture = Resources::Load<Texture>(L"Stage0_ForestDg02_Map", L"..\\Resources\\Map\\Stage0\\stage0_forestdg_2.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"Stage0ForestDg02_Map", material);

		// Stage0_ForestDg03 Map
		texture = Resources::Load<Texture>(L"Stage0_ForestDg03_Map", L"..\\Resources\\Map\\Stage0\\stage0_forestdg_3.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"Stage0ForestDg03_Map", material);

		// Stage0_ForestDg04 Map
		texture = Resources::Load<Texture>(L"Stage0_ForestDg04_Map", L"..\\Resources\\Map\\Stage0\\stage0_forestdg_4.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"Stage0ForestDg04_Map", material);


#pragma endregion


#pragma region Item Icon
		texture = Resources::Load<Texture>(L"Item_BonusLife", L"..\\Resources\\Item\\BonusLife.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"BonusLife", material);

		texture = Resources::Load<Texture>(L"Item_StealHP", L"..\\Resources\\Item\\StealHP.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"StealHP", material);

		texture = Resources::Load<Texture>(L"Item_HealHP", L"..\\Resources\\Item\\HealHP.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"HealHP", material);

		texture = Resources::Load<Texture>(L"Item_EStrength", L"..\\Resources\\Item\\enhencestrength.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"EStrength", material);

		texture = Resources::Load<Texture>(L"Item_EDefence", L"..\\Resources\\Item\\enhencedefence.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"EDefence", material);

		texture = Resources::Load<Texture>(L"Item_ERange", L"..\\Resources\\Item\\enhencerange.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"ERange", material);

		texture = Resources::Load<Texture>(L"Item_EAduration", L"..\\Resources\\Item\\enhenceattackduration.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"EAduration", material);

		texture = Resources::Load<Texture>(L"Item_EAcount", L"..\\Resources\\Item\\enhenceattackcount.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"EAcount", material);

		texture = Resources::Load<Texture>(L"Item_Eprojs", L"..\\Resources\\Item\\enhenceprojs.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"Eprojs", material);

		texture = Resources::Load<Texture>(L"Item_EAspeed", L"..\\Resources\\Item\\enhenceattackspeed.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"EAspeed", material);

		texture = Resources::Load<Texture>(L"Item_Espeed", L"..\\Resources\\Item\\enhencespeed.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"Espeed", material);

		texture = Resources::Load<Texture>(L"Item_EmaxHP", L"..\\Resources\\Item\\enhencemaxhp.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"EmaxHP", material);

		texture = Resources::Load<Texture>(L"Item_Cheese", L"..\\Resources\\Item\\item_cheese.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"Item_Cheeseicon", material);

		texture = Resources::Load<Texture>(L"Item_Lucy", L"..\\Resources\\Item\\item_lucy.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"Item_Lucyicon", material);

		texture = Resources::Load<Texture>(L"Item_Robo", L"..\\Resources\\Item\\item_robo.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"Item_Roboicon", material);

#pragma endregion

#pragma region Character
		// 임시 치즈
		texture = Resources::Load<Texture>(L"Cheese_t", L"..\\Resources\\Character\\Cheese\\HeroBody_08.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"Cheese_temp", material);

#pragma endregion
#pragma region Bullet

		// Cheese Bullet
		texture = Resources::Load<Texture>(L"Cheese_Arrow", L"..\\Resources\\Character\\Cheese\\arrow.png");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"Arrow", material);

#pragma endregion

#pragma region Monster

		texture = Resources::Load<Texture>(L"Monster_SlimeA", L"..\\Resources\\Monster\\SlimeA.png");
		material = std::make_shared<Material>();
		material->SetShader(AniShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"MobSlimeA", material);

		texture = Resources::Load<Texture>(L"Monster_SlimeB", L"..\\Resources\\Monster\\SlimeB.png");
		material = std::make_shared<Material>();
		material->SetShader(AniShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"MobSlimeB", material);

		texture = Resources::Load<Texture>(L"Monster_CannibalFlowerA", L"..\\Resources\\Monster\\CannibalFlowerA.png");
		material = std::make_shared<Material>();
		material->SetShader(AniShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"MobCannibalFlowerA", material);


		texture = Resources::Load<Texture>(L"Monster_Ent", L"..\\Resources\\Monster\\Ent.png");
		material = std::make_shared<Material>();
		material->SetShader(AniShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"MobEnt", material);

		texture = Resources::Load<Texture>(L"Monster_Larva", L"..\\Resources\\Monster\\Larva.png");
		material = std::make_shared<Material>();
		material->SetShader(AniShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"MobLarva", material);

		texture = Resources::Load<Texture>(L"Monster_EliteLarva", L"..\\Resources\\Monster\\EliteLarva.png");
		material = std::make_shared<Material>();
		material->SetShader(AniShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"MobEliteLarva", material);

		texture = Resources::Load<Texture>(L"Monster_Cannibals", L"..\\Resources\\Monster\\Cannibals.png");
		material = std::make_shared<Material>();
		material->SetShader(AniShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"MobCannibals", material);

		texture = Resources::Load<Texture>(L"Monster_EliteCannibals", L"..\\Resources\\Monster\\EliteCannibals.png");
		material = std::make_shared<Material>();
		material->SetShader(AniShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"MobEliteCannibals", material);

		texture = Resources::Load<Texture>(L"Monster_OldEnt", L"..\\Resources\\Monster\\Bosses\\OldEnt.png");
		material = std::make_shared<Material>();
		material->SetShader(AniShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"MobOldEnt", material);

		texture = Resources::Load<Texture>(L"Monster_SkelKnight", L"..\\Resources\\Monster\\Bosses\\skeletonknight.png");
		material = std::make_shared<Material>();
		material->SetShader(AniShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"MobSkelKnight", material);

#pragma endregion
	}

	void Initialize()
	{
		LoadMesh();
		LoadBuffer();
		LoadShader();
		SetupState();
		LoadTexture();
		LoadMaterial();
	}

	void BindLights()
	{
		std::vector<LightAttribute> lightsAttributes = {};
		for (Light* light : lights)
		{
			LightAttribute attribute = light->GetAttribute();
			lightsAttributes.push_back(attribute);
		}
		lightsBuffer->SetData(lightsAttributes.data(), lightsAttributes.size());
		lightsBuffer->BindSRV(eShaderStage::VS, 13);
		lightsBuffer->BindSRV(eShaderStage::PS, 13);

	}

	void BindNoiseTexture()
	{
		std::shared_ptr<Texture> texture
			= Resources::Find<Texture>(L"Noise01");

		texture->BindShaderResource(eShaderStage::VS, 15);
		texture->BindShaderResource(eShaderStage::HS, 15);
		texture->BindShaderResource(eShaderStage::DS, 15);
		texture->BindShaderResource(eShaderStage::GS, 15);
		texture->BindShaderResource(eShaderStage::PS, 15);
		texture->BindShaderResource(eShaderStage::CS, 15);

		ConstantBuffer* cb = constantBuffer[(UINT)eCBType::Noise];
		NoiseCB data = {};
		data.size.x = texture->GetWidth();
		data.size.y = texture->GetHeight();

		cb->SetData(&data);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::CS);

	}


	void Render()
	{
		BindNoiseTexture();
		BindLights();
		for (Camera* cam : cameras)
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras.clear();
		lights.clear();
	}

	void Release()
	{
		for (ConstantBuffer* buff : constantBuffer)
		{
			if (buff == nullptr)
				continue;

			delete buff;
			buff = nullptr;
		}

		delete lightsBuffer;
		lightsBuffer = nullptr;
	}
	void PushDebugMeshAttribute(DebugMesh& mesh)
	{
		debugMeshs.push_back(mesh);
	}
}