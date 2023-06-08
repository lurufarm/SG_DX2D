#include "sgConstantBuffer.h"
#include "sgGraphicDevice_Dx11.h"

namespace sg::graphics
{
	ConstantBuffer::ConstantBuffer(const eCBType type)
		: GpuBuffer()
		, mType(type)
	{
	}
	ConstantBuffer::~ConstantBuffer()
	{
	}
	bool ConstantBuffer::Create(size_t size)
	{
		desc.ByteWidth = size;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		sg::graphics::GetDevice()->CreateBuffer(buffer.GetAddressOf(), &desc, nullptr);

		return true;
	}
	void ConstantBuffer::SetData(void* data)
	{
		sg::graphics::GetDevice()->SetConstantBuffer(buffer.Get(), data, desc.ByteWidth);
	}
	void ConstantBuffer::Bind(eShaderStage stage)
	{
		sg::graphics::GetDevice()->BindConstantBuffer(stage, mType, buffer.Get());
	}
}