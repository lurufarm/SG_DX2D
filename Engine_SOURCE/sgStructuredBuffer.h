#pragma once
#include "sgEntity.h"
#include "sgGraphics.h"

namespace sg::graphics
{
	class StructuredBuffer : public GpuBuffer
	{
	public:
		StructuredBuffer();
		~StructuredBuffer();

		bool Create(UINT size, UINT stride, eViewType type, void* data, bool cpuAccess = false);
		bool CreateRWBuffer();
		void SetData(void* data, UINT stride);
		void GetData(void* data, UINT size);
		void BindSRV(eShaderStage stage, UINT slot);
		void BindUAV(UINT slot);

		void Clear();

		UINT GetSize() { return mSize; }
		UINT GetStride() { return mStride; }

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> mReadBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> mWriteBuffer;

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> mUAV;
		eViewType mType;

		UINT mSize;
		UINT mStride;

		UINT mSRVSlot;
		UINT mUAVSlot;

	};
}
