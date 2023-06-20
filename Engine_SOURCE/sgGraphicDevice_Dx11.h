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

		void BindInputLayout(ID3D11InputLayout* pInputLayout);
		void BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology);
		void BindVertexBuffer(UINT startslot, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets);
		void BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT format, UINT offset);
		void BindVertexShader(ID3D11VertexShader* pVertexShader);
		void BIndPixelShader(ID3D11PixelShader* pPixelShader);
		void SetConstantBuffer(ID3D11Buffer* buffer, void* data, UINT size);
		void BindConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer);
		void BindConstantBuffers(eShaderStage stage, eCBType type, ID3D11Buffer* buffer);
		void BindShaderResource(eShaderStage stage, UINT startSlot, ID3D11ShaderResourceView** ppSRV);
		void BindSampler(eShaderStage stage, UINT StartSlot, ID3D11SamplerState** ppSamplers);
		void BindViewPort(D3D11_VIEWPORT* viewport);
		
		void DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
		void ClearTarget();
		void UpdateViewPort();
		void Draw();
		void Present();
		//void Draw(UINT indexnum);

		ID3D11Device* GetID3D11Device() { return mDevice.Get(); }


	private:
		// 실제 그래픽 카드 하드웨어 객체
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;

		// dx11에서 직접적으로 디바이스에 객체에 접근하지 않고, 이 객체를 이용하여 명령을 내린다.
		// Context의 의미를 명령, 호출 등으로 생각하면 좋다.
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;

		// 최종적으로 그려질 텍스쳐(도화지)
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTarget;

		// 렌더타겟에 직접 접근하지 않고 레더타겟 뷰를 통해 접근한다.
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;

		// 깊이 버퍼
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilBuffer;

		// 깊이 버퍼에 접근할 수 있는 뷰
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;

		// 더블버퍼링 작업을 진행해주는 Swap Chain
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;

		D3D11_VIEWPORT mViewPort;

	};

	inline GraphicDevice_Dx11*& GetDevice()
	{
		static GraphicDevice_Dx11* device = nullptr;
		return device;
	}
}

