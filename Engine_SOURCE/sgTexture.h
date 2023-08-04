#pragma once
#include "sgResource.h"
#include "sgGraphics.h"

#include "../External/DirectXTex/Include/DirectXTex.h"
#include "../External/DirectXTex/Include/DirectXTex.inl"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\DirectXTex\\Lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\External\\DirectXTex\\Lib\\Release\\DirectXTex.lib")
#endif

namespace sg::graphics
{
	//using namespace sg::math;

	class Texture : public Resource
	{
	public:
		Texture();
		~Texture();

		bool Create(UINT width, UINT height, DXGI_FORMAT format, UINT bindFlag);
		virtual HRESULT Load(const std::wstring& path) override;
		void BindShaderResource(eShaderStage stage, UINT startSlot);
		void BindUnorderedAccessViews(UINT slot);
		void ClearUnorderedAccessViews(UINT slot);
		void Clear();

		float GetWidth() { return mWidth; }
		float GetHeight() { return mHeight; }

		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		GetRTV()		{ return mRTV; }
		void SetRTV(Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv)		{ mRTV = rtv; }
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	GetSRV()		{ return mSRV; }
		void SetDSV(Microsoft::WRL::ComPtr<ID3D11DepthStencilView> dsv)		{ mDSV = dsv; }
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>		GetDSV()		{ return mDSV; }
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView>	GetUAV()		{ return mUAV; }
		Microsoft::WRL::ComPtr<ID3D11Texture2D>				GetTexture()	{ return mTexture; }
		void SetTexture(Microsoft::WRL::ComPtr<ID3D11Texture2D> texture)	{ mTexture = texture; }

	private:
		ScratchImage mImage;

		Microsoft::WRL::ComPtr<ID3D11Texture2D>				mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	mSRV;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		mRTV;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>		mDSV;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView>	mUAV;

		float mWidth;
		float mHeight;

		D3D11_TEXTURE2D_DESC mDesc;
	};
}
