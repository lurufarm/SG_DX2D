#include "sgFontWrapper.h"
#include "sgGraphicDevice_Dx11.h"
#include "..\LuruEngine\Gobj_Font.h"

namespace sg
{
	IFW1Factory* FontWrapper::mFW1Factory = nullptr;
	IFW1FontWrapper* FontWrapper::mFontWrapper = nullptr;
	std::vector<Gobj_Font*> FontWrapper::mAllText = {};
	WCHAR FontWrapper::mText[100] = {};
	float FontWrapper::mXpos = 0.0f;
	float FontWrapper::mYpos = 0.0f;
	float FontWrapper::mFontSize = 0.0f;
	UINT FontWrapper::mFontColor = 0;
	
	bool FontWrapper::Initialize()
	{
		if (FAILED(FW1CreateFactory(FW1_VERSION, &mFW1Factory)))
			return false;

		ID3D11Device* pDevice = graphics::GetDevice()->GetID3D11Device();

		if (FAILED(mFW1Factory->CreateFontWrapper(pDevice, L"Arial", &mFontWrapper)))
			return false;

		return true;
	}
	void FontWrapper::Render()
	{
		for (Gobj_Font* text : mAllText)
		{
			if (text->GetText().empty())
				continue;

			Vector3 FontOption = text->GetFontOption();
			UINT FontColor = text->GetFontColor();
			DrawFont(text->GetText().c_str(), FontOption.x, FontOption.y, FontOption.z, FontColor);
		}
		mAllText.clear();
	}
	void FontWrapper::Release()
	{
		mFW1Factory->Release();
		mFW1Factory = nullptr;

		mFontWrapper->Release();
		mFontWrapper = nullptr;
	}
	void FontWrapper::DrawFont(const WCHAR* str, float x, float y, float size, UINT rgb)
	{
		ID3D11DeviceContext* pContext = graphics::GetDevice()->GetID3D11DeviceContext();
		mFontWrapper->DrawString(
			pContext,
			str,
			size,
			x,
			y,
			rgb,
			FW1_RESTORESTATE);
	}
	void FontWrapper::SetFontOption(float x, float y, float size, UINT rgb)
	{
		mXpos = x;
		mYpos = y;
		mFontSize = size;
		mFontColor = rgb;
	}
}