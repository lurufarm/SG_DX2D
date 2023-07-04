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

		shader = sg::Resources::Find<Shader>(L"CatPatternShader");
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
	
	void LoadBuffer()
	{
		// Vertex Buffer 설정
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", mesh);

		mesh->CreateVertexBuffer(vertexes, 4);

		// Index Buffer 설정
		std::vector<UINT> indexes = {};
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());

		// Constant Buffer 설정
		constantBuffer[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		constantBuffer[(UINT)eCBType::Time] = new ConstantBuffer(eCBType::Time);
		constantBuffer[(UINT)eCBType::Time]->Create(sizeof(TimeCB));


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



		{ // Test
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"Cat", L"..\\Resources\\Texture\\Cat.png");

			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			Resources::Insert(L"SpriteMaterial", spriteMaterial);
		}

		{ // BGImg
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"Title", L"..\\Resources\\Title\\title.png");

			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			Resources::Insert(L"ImgTitle01", spriteMaterial);
		}
		{ // TItle logo
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"Logo", L"..\\Resources\\Title\\Logo01.png");

			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRendereringMode(eRenderingMode::CutOut);
			Resources::Insert(L"ImgLogo01", spriteMaterial);
		}
		{ // Select - Story
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"Story", L"..\\Resources\\Title\\ModeIllust_Story.png");

			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRendereringMode(eRenderingMode::CutOut);
			Resources::Insert(L"ImgStory", spriteMaterial);
		}
		{ // Select - Party
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"Party", L"..\\Resources\\Title\\ModeIllust_Party.png");

			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRendereringMode(eRenderingMode::CutOut);
			Resources::Insert(L"ImgParty", spriteMaterial);
		}
		{ // Select - CatPattern
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"CatPattern", L"..\\Resources\\Title\\CatPattern.png");

			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(catPatternShader);
			spriteMaterial->SetTexture(texture);
			//spriteMaterial->SetRendereringMode(eRenderingMode::CutOut);
			Resources::Insert(L"ImgCatPattern", spriteMaterial);
		}
		{ // Lobby - BG1
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"Space1", L"..\\Resources\\Lobby\\SvSpace.png");

			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(SpaceShader1);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRendereringMode(eRenderingMode::CutOut);
			Resources::Insert(L"ImgSpace1", spriteMaterial);
		}
		{ // Lobby - BG2
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"Space2", L"..\\Resources\\Lobby\\SvSpace2.png");

			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(SpaceShader2);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRendereringMode(eRenderingMode::CutOut);
			Resources::Insert(L"ImgSpace2", spriteMaterial);
		}
		{ // Lobby_map
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"Lobby", L"..\\Resources\\Lobby\\Lobby.png");

			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRendereringMode(eRenderingMode::CutOut);
			Resources::Insert(L"ImgLobbyMap", spriteMaterial);
		}
		{ // UI_Exit Button
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"ExitButton", L"..\\Resources\\UI\\NavButton_12.png");

			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRendereringMode(eRenderingMode::CutOut);
			Resources::Insert(L"UIExitButton", spriteMaterial);
		}
		{ // UI_SelectBox 0 (top left)
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"UI_SelectBox_tl", L"..\\Resources\\UI\\selectbox_tl.png");

			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRendereringMode(eRenderingMode::Transparent);
			Resources::Insert(L"UISBox_tl", spriteMaterial);
		}
		{ // UI_SelectBox 1 (top right)
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"UI_SelectBox_tr", L"..\\Resources\\UI\\selectbox_tr.png");

			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRendereringMode(eRenderingMode::Transparent);
			Resources::Insert(L"UISBox_tr", spriteMaterial);
		}
		{ // UI_SelectBox 2 (bottom left)
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"UI_SelectBox_bl", L"..\\Resources\\UI\\selectbox_bl.png");

			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRendereringMode(eRenderingMode::Transparent);
			Resources::Insert(L"UISBox_bl", spriteMaterial);
		}
		{ // UI_SelectBox 3 (bottom right)
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"UI_SelectBox_br", L"..\\Resources\\UI\\selectbox_br.png");

			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			spriteMaterial->SetRendereringMode(eRenderingMode::Transparent);
			Resources::Insert(L"UISBox_br", spriteMaterial);
		}
	}

	void Initialize()
	{
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

		LoadBuffer();
		LoadShader();
		SetupState();

	}
	void Update()
	{
		//if (Input::KeyP(eKeyCode::W) || Input::KeyD(eKeyCode::W))
		//{
		//	MovePos.y += 0.5 * Time::DeltaTime();
		//}
		//else if (Input::KeyP(eKeyCode::S) || Input::KeyD(eKeyCode::S))
		//{
		//	MovePos.y -= 0.5 * Time::DeltaTime();
		//}
		//if (Input::KeyP(eKeyCode::A) || Input::KeyD(eKeyCode::A))
		//{
		//	MovePos.x -= 0.5 * Time::DeltaTime();
		//}
		//else if (Input::KeyP(eKeyCode::D) || Input::KeyD(eKeyCode::D))
		//{
		//	MovePos.x += 0.5 * Time::DeltaTime();
		//}

		//constantBuffer->SetData(&MovePos);
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