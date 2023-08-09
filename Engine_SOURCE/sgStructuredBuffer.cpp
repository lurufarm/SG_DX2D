#include "sgStructuredBuffer.h"
#include "sgGraphicDevice_Dx11.h"

namespace sg::graphics
{
	StructuredBuffer::StructuredBuffer()
		: mSRV(nullptr)
		, mType(eSRVType::None)
		, mSize(0)
		, mStride(0)
	{
	}
	StructuredBuffer::~StructuredBuffer()
	{
	}
	bool StructuredBuffer::Create(UINT size, UINT stride, eSRVType type)
	{
		mSize = size;
		mStride = stride;

		desc.ByteWidth = mSize * stride;
		desc.StructureByteStride = mSize;

		desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
		desc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

		if (!GetDevice()->CreateBuffer(buffer.GetAddressOf(), &desc, nullptr))
			return false;

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.BufferEx.NumElements = mStride;
		srvDesc.ViewDimension = D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_BUFFEREX;

		if (!(GetDevice()->CreateShaderResourceView(buffer.Get(), &srvDesc, mSRV.GetAddressOf())))
			return false;

		return true;
	}
	void StructuredBuffer::SetData(void* data, UINT stride)
	{
		if (mStride < stride)
			Create(mSize, stride, eSRVType::None);

		if (buffer.Get() != nullptr)
		{
			GetDevice()->BindBuffer(buffer.Get(), data, mSize * stride);
		}

		//D3D11_BUFFER_DESC newdesc = {};
		//GetDevice()->CreateBuffer(buffer.GetAddressOf(), &newdesc, nullptr);

	}
	void StructuredBuffer::BindSRV(eShaderStage stage, UINT slot)
	{
		mSRVSlot = slot;
		GetDevice()->BindShaderResource(stage, slot, mSRV.GetAddressOf());
	}
	void StructuredBuffer::BindUAV(UINT slot)
	{
		mUAVslot = slot;
		UINT i = -1;
		GetDevice()->BindUnorderedAccess(slot, mUAV.GetAddressOf(), &i);

	}
	void StructuredBuffer::Clear()
	{
		ID3D11ShaderResourceView* srv = nullptr;
		GetDevice()->BindShaderResource(eShaderStage::VS, mSRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::HS, mSRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::DS, mSRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::GS, mSRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::PS, mSRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::CS, mSRVSlot, &srv);

		ID3D11UnorderedAccessView* uav = nullptr;
		UINT i = -1;
		GetDevice()->BindUnorderedAccess(mUAVslot, &uav, &i);
	}
}