#include "sgRenderer.h"
#include "sgInput.h"
#include "sgTime.h"

#include "sgResources.h"
#include "sgTexture.h"
#include "sgMaterial.h"

namespace renderer
{
	using namespace sg;
	using namespace sg::graphics;

	Vertex vertexes[4] = {};

	sg::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End] = {};

	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};
	
	std::vector<sg::Camera*> cameras = {};

	void SetupState()
	{
#pragma region Input Layout
		// Input Layout ���� ������ ������ �Ѱ��ش�.
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

		shader = sg::Resources::Find<Shader>(L"GridShader");
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




#pragma endregion
#pragma region Sampler State
		// Sampler State
		D3D11_SAMPLER_DESC pdesc = {};
		pdesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		pdesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		pdesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		pdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		GetDevice()->CreateSampler(&pdesc, samplerState[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 0, samplerState[(UINT)eSamplerType::Point].GetAddressOf());

		D3D11_SAMPLER_DESC adesc = {};
		adesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		adesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		adesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		adesc.MaxAnisotropy = 4;
		adesc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSampler(&adesc, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
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
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
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
		// RECT
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
	}

	void LoadBuffer()
	{
		// Vertex Buffer ����
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", mesh);

		mesh->CreateVertexBuffer(vertexes, 4);

		// Index Buffer ����
		std::vector<UINT> indexes = {};
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());

		// Constant Buffer ����
		constantBuffer[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		// Constant Buffer - Time
		constantBuffer[(UINT)eCBType::Time] = new ConstantBuffer(eCBType::Time);
		constantBuffer[(UINT)eCBType::Time]->Create(sizeof(TimeCB));

		// Constant Buffer - Grid
		constantBuffer[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffer[(UINT)eCBType::Grid]->Create(sizeof(GridCB));



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

		std::shared_ptr<Shader> gridShader = std::make_shared<Shader>();
		gridShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		gridShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		sg::Resources::Insert(L"GridShader", gridShader);

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

	}

	void LoadMaterial()
	{
#pragma region Find Shader
		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteShader");

		std::shared_ptr<Shader> catPatternShader
			= Resources::Find<Shader>(L"CatPatternShader");

		std::shared_ptr<Shader> SpaceShader1
			= Resources::Find<Shader>(L"lobby_spaceShader1");

		std::shared_ptr<Shader> SpaceShader2
			= Resources::Find<Shader>(L"lobby_spaceShader2");
#pragma endregion
#pragma region Basic Texture and Basic Material declaration 
		std::shared_ptr<Texture> texture;
		std::shared_ptr<Material> material;

		// Test
		texture	= Resources::Load<Texture>(L"Cat", L"..\\Resources\\Texture\\Cat.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"SpriteMaterial", material);

		// Grid

		std::shared_ptr<Shader>gridShader
			= Resources::Find<Shader>(L"GridShader");
		material = std::make_shared<Material>();
		material->SetShader(gridShader);
		Resources::Insert(L"GridMaterial", material);

#pragma endregion
#pragma region Title Scene Material

		 // BGImg
		texture = Resources::Load<Texture>(L"Title", L"..\\Resources\\Title\\title.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Opaque);
		Resources::Insert(L"ImgTitle01", material);
		
		 // TItle logo
		texture = Resources::Load<Texture>(L"Logo", L"..\\Resources\\Title\\Logo01.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"ImgLogo01", material);
		
#pragma endregion
#pragma region Select Scene Material
		 // Select - Story
		texture	= Resources::Load<Texture>(L"Story", L"..\\Resources\\Title\\ModeIllust_Story.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"ImgStory", material);

		texture = Resources::Load<Texture>(L"Story_text", L"..\\Resources\\Title\\Title_StoryMode.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"ImgStory_text", material);
		
		 // Select - Party
		texture = Resources::Load<Texture>(L"Party", L"..\\Resources\\Title\\ModeIllust_Party.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"ImgParty", material);

		texture = Resources::Load<Texture>(L"Party_text", L"..\\Resources\\Title\\Title_PartyMode.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"ImgParty_text", material);
		
		 // Select - CatPattern
		texture = Resources::Load<Texture>(L"CatPattern", L"..\\Resources\\Title\\CatPattern.png");
		material = std::make_shared<Material>();
		material->SetShader(catPatternShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"ImgCatPattern", material);

		
#pragma endregion
#pragma region Lobby Scene Material
		 // Lobby - BG1
		texture = Resources::Load<Texture>(L"Space1", L"..\\Resources\\Lobby\\SvSpace.png");
		material = std::make_shared<Material>();
		material->SetShader(SpaceShader1);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"ImgSpace1", material);
		
		 // Lobby - BG2
		texture	= Resources::Load<Texture>(L"Space2", L"..\\Resources\\Lobby\\SvSpace2.png");
		material = std::make_shared<Material>();
		material->SetShader(SpaceShader2);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"ImgSpace2", material);
		
		 // Lobby_map
		texture = Resources::Load<Texture>(L"Lobby", L"..\\Resources\\Lobby\\Lobby.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"ImgLobbyMap", material);
		
		 // Lobby_Character
		texture = Resources::Load<Texture>(L"Lobby_Character", L"..\\Resources\\Lobby\\SurvivalCharacter_01.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"InteractableLobbyCharacter", material);

		
		 // Lobby_Upgrade
		texture = Resources::Load<Texture>(L"Lobby_Upgrade", L"..\\Resources\\Lobby\\SurvivalUpgrade_01.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"InteractableLobbyUpgrade", material);

		
		 // Lobby_Gate

		
		 // Lobby_Molding
		texture = Resources::Load<Texture>(L"Lobby_Molding", L"..\\Resources\\Lobby\\SvMolding.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"ImgMolding", material);

		
#pragma endregion
#pragma region UI Material
		 // UI_Exit Button
		texture = Resources::Load<Texture>(L"ExitButton", L"..\\Resources\\UI\\NavButton_12.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::CutOut);
		Resources::Insert(L"UIExitButton", material);
		
		 // UI_SelectBox 0 (top left)
		texture = Resources::Load<Texture>(L"UI_SelectBox_tl", L"..\\Resources\\UI\\selectbox_tl.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"UISBox_tl", material);
		
		 // UI_SelectBox 1 (top right)
		texture = Resources::Load<Texture>(L"UI_SelectBox_tr", L"..\\Resources\\UI\\selectbox_tr.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"UISBox_tr", material);
		
		 // UI_SelectBox 2 (bottom left)
		texture = Resources::Load<Texture>(L"UI_SelectBox_bl", L"..\\Resources\\UI\\selectbox_bl.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"UISBox_bl", material);
		
		 // UI_SelectBox 3 (bottom right)
		texture = Resources::Load<Texture>(L"UI_SelectBox_br", L"..\\Resources\\UI\\selectbox_br.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		material->SetRendereringMode(eRenderingMode::Transparent);
		Resources::Insert(L"UISBox_br", material);
		
#pragma endregion

	}

	void Initialize()
	{
		LoadMesh();
		LoadBuffer();
		LoadShader();
		SetupState();
		LoadMaterial();
	}

	void Update()
	{
	}

	void Render()
	{
		for (Camera* cam : cameras)
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras.clear();
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
	}
}