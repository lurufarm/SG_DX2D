#pragma once

#include "LuruEngine.h"
#include "sgGraphics.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace sg::graphics
{
	class GraphicDevice_Dx11
	{
	public:
		GraphicDevice_Dx11();
		~GraphicDevice_Dx11();

		bool CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* desc, HWND hWnd);
		bool CreateBuffer(ID3D11Buffer** buffer, D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data);
		bool CreateShader();

		bool CreateTexture(const D3D11_TEXTURE2D_DESC* desc, void* data);


		void BindViewPort(D3D11_VIEWPORT* viewport);

		void SetConstantBuffer(ID3D11Buffer* buffer, void* data, UINT size);
		void BindConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer);
		void BindConstantBuffers(eShaderStage stage, eCBType type, ID3D11Buffer* buffer);

		void Draw();
		void Draw(UINT indexnum);

	private:
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

