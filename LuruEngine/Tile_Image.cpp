#include "Tile_Image.h"
#include "sgApplication.h"
#include "sgResources.h"

extern sg::Application application;

namespace sg
{
	std::shared_ptr<Tile_Image> Tile_Image::Create(const std::wstring& name, UINT widht, UINT height, COLORREF rgb)
	{
		if (widht == 0 || height == 0)
			return nullptr;

		std::shared_ptr<Tile_Image> image = Resources::Find<Tile_Image>(name);
		if (image != nullptr)
			return image;

		image = std::make_shared<Tile_Image>();
		HDC mainHdc = GetDC(application.GetToolHwnd());

		image->mBitmap = CreateCompatibleBitmap(mainHdc, widht, height);

		image->mHdc = CreateCompatibleDC(mainHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(image->mHdc, image->mBitmap);
		DeleteObject(oldBitmap);

		image->mWidth = widht;
		image->mHeight = height;

		image->SetKey(name);
		Resources::Insert<Tile_Image>(name, image);

		// Setting Tile_Image Color
		HBRUSH brush = CreateSolidBrush(rgb);
		HBRUSH oldBrush = (HBRUSH)SelectObject(image->GetHdc(), brush);
		::Rectangle(image->GetHdc(), -1, -1, image->mWidth + 1, image->mHeight + 1);
		SelectObject(image->GetHdc(), oldBrush);
		DeleteObject(oldBrush);

		return image;
	}
	Tile_Image::Tile_Image()
		: Resource(enums::eResourceType::Tile_Image)
		, mBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
	{


	}

	Tile_Image::~Tile_Image()
	{

	}

	HRESULT Tile_Image::Load(const std::wstring& path)
	{
		mBitmap = (HBITMAP)LoadImageW(nullptr
			, path.c_str(), IMAGE_BITMAP
			, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (mBitmap == nullptr)
			return E_FAIL;

		BITMAP bitInfo = {};
		GetObject(mBitmap, sizeof(BITMAP), &bitInfo);

		mWidth = bitInfo.bmWidth;
		mHeight = bitInfo.bmHeight;

		HDC mainDC = GetDC(application.GetToolHwnd());
		mHdc = CreateCompatibleDC(mainDC);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
		DeleteObject(oldBitmap);

		return S_OK;
	}
	COLORREF Tile_Image::GetPixel(int x, int y)
	{
		return ::GetPixel(mHdc, x, y);
	}
	void Tile_Image::SetPixel(int x, int y, COLORREF color)
	{
		::SetPixel(mHdc, x, y, color);
	}
}