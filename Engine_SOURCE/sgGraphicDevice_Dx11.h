#pragma once

#include "LuruEngine.h"
#include "sgGraphics.h"

namespace sg::graphics
{
	class GraphicDevice_Dx11
	{
	public:
		GraphicDevice_Dx11();
		~GraphicDevice_Dx11();

		bool CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* desc, HWND hWnd);
		bool CreateTexture(const D3D11_TEXTURE2D_DESC* desc, void* data);
		bool CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT , ID3DBlob* bytecode, ID3D11InputLayout** ppInputLayout);
		bool CreateBuffer(ID3D11Buffer** buffer, D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data);
		bool CompileFromfile(const std::wstring& filename, const std::string& funcname, const std::string& version, ID3DBlob** ppCode);
		bool CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11VertexShader** ppVertexShader);
		bool CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11PixelShader** ppPixelShader);
		bool CreateSampler(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState);
		bool CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc, ID3D11RasterizerState** ppRasterizerState);
		bool CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc, ID3D11DepthStencilState** ppDepthStencilState);
		bool CreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc, ID3D11BlendState** ppBlendState);
		bool CreateShaderResourceView(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D11ShaderResourceView** ppSRView);

		void BindInputLayout(ID3D11InputLayout* pInputLayout);
		void BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology);
		void BindVertexBuffer(UINT startslot, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets);
		void BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT format, UINT offset);
		void BindVertexShader(ID3D11VertexShader* pVertexShader);
		void BIndPixelShader(ID3D11PixelShader* pPixelShader);
		void SetConstantBuffer(ID3D11Buffer* buffer, void* data, UINT size);
		void BindConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer);
		void BindConstantBuffers(eShaderStage stage, eCBType type, ID3D11Buffer* buffer);
		void BindBuffer(ID3D11Buffer* buffer, void* data, UINT size);
		void BindShaderResource(eShaderStage stage, UINT startSlot, ID3D11ShaderResourceView** ppSRV);
		void BindSampler(eShaderStage stage, UINT StartSlot, ID3D11SamplerState** ppSamplers);
		void BindViewPort(D3D11_VIEWPORT* viewport);
		void BindRasterizerState(ID3D11RasterizerState* pRasterizerState);
		void BindDepthStencilState(ID3D11DepthStencilState* pDepthStencilState);
		void BindBlendState(ID3D11BlendState* pBlendState);

		
		void DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
		void ClearTarget();
		void UpdateViewPort();
		void Draw();
		void Present();

		void SetBgColor(float* color)
		{
			mBgcolor[0] = color[0];
			mBgcolor[1] = color[1];
			mBgcolor[2] = color[2];
			mBgcolor[3] = 1.0f;
		}

		//void Draw(UINT indexnum);

		ID3D11Device* GetID3D11Device() { return mDevice.Get(); }


	private:

		float mBgcolor[4];

		// ���� �׷��� ī�� �ϵ���� ��ü
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;

		// dx11���� ���������� ����̽��� ��ü�� �������� �ʰ�, �� ��ü�� �̿��Ͽ� ����� ������.
		// Context�� �ǹ̸� ���, ȣ�� ������ �����ϸ� ����.
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;

		// ���������� �׷��� �ؽ���(��ȭ��)
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTarget;

		// ����Ÿ�ٿ� ���� �������� �ʰ� ����Ÿ�� �並 ���� �����Ѵ�.
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;

		// ���� ����
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilBuffer;

		// ���� ���ۿ� ������ �� �ִ� ��
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;

		// ������۸� �۾��� �������ִ� Swap Chain
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;

		D3D11_VIEWPORT mViewPort;

	};

	inline GraphicDevice_Dx11*& GetDevice()
	{
		static GraphicDevice_Dx11* device = nullptr;
		return device;
	}
}

