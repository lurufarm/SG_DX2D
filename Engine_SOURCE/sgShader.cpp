#include "sgShader.h"

namespace sg
{
	Shader::Shader()
		: mInputLayout(nullptr)
		, mTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	{
	}
	Shader::~Shader()
	{
		mInputLayout->Release();
	}
	HRESULT Shader::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}
	bool Shader::Create(const eShaderStage stage
		, const std::wstring& filename
		, const std::string& funcname)
	{
		std::filesystem::path shaderpath
			= std::filesystem::current_path().parent_path();
		shaderpath += L"\\Shader_SOURCE\\";

		std::filesystem::path fullpath(shaderpath.c_str());
		fullpath += filename;

		ID3DBlob* errorBlob = nullptr;
		if (stage == eShaderStage::VS)
		{
			GetDevice()->CompileFromfile(fullpath, funcname, "vs_5_0", mVSBlob.GetAddressOf());
			GetDevice()->CreateVertexShader(mVSBlob->GetBufferPointer()
				, mVSBlob->GetBufferSize(), mVS.GetAddressOf());
		}
		else if (stage == eShaderStage::PS)
		{
			GetDevice()->CompileFromfile(fullpath, funcname, "ps_5_0", mPSBlob.GetAddressOf());
			GetDevice()->CreatePixelShader(mPSBlob->GetBufferPointer()
				, mPSBlob->GetBufferSize(), mPS.GetAddressOf());
		}
		return true;
	}
	void Shader::Binds()
	{
		GetDevice()->BindPrimitiveTopology(mTopology);
		GetDevice()->BindInputLayout(mInputLayout);
		GetDevice()->BindVertexShader(mVS.Get());
		GetDevice()->BIndPixelShader(mPS.Get());
	}
}