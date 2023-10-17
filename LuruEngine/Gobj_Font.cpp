#include "Gobj_Font.h"

namespace sg
{
	Gobj_Font::Gobj_Font()
	{
		Gobj_Font::Initialize();
	}
	Gobj_Font::~Gobj_Font()
	{
	}
	void Gobj_Font::Initialize()
	{
		mTr = GetComp<Transform>();

		FW1CreateFactory(FW1_VERSION, &mFW1Factory);
		ID3D11Device* pDevice = graphics::GetDevice()->GetID3D11Device();
		mFW1Factory->CreateFontWrapper(pDevice, L"Arial", &mFontWrapper);
		mText[100] = {};
		mXpos = 0;
		mYpos = 0;
		mFontSize = 0;
		mFontColor = 0;
	}
	void Gobj_Font::Update()
	{
		FontWrapper::AddText(this);
		GameObject::Update();
	}
	void Gobj_Font::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Gobj_Font::Render()
	{
		GameObject::Render();
	}
	void Gobj_Font::SetFontOption(float x, float y, float size, UINT rgb)
	{
		mXpos = x;
		mYpos = y;
		mFontSize = size;
		mFontColor = rgb;
	}
	void Gobj_Font::SetText(const wchar_t text[])
	{
		wcscpy_s(mText, text);
	}
}