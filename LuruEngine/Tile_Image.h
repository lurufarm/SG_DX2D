#pragma once
#include "..\Engine_SOURCE\sgResource.h"

namespace sg
{
	class Tile_Image : public Resource
	{
	public:

		static std::shared_ptr<Tile_Image> Create(const std::wstring& name, UINT widht, UINT height, COLORREF rgb = RGB(255, 255, 255));

		Tile_Image();
		~Tile_Image();

		virtual HRESULT Load(const std::wstring& path) override;
		//void SetColor(UCHAR r, UCHAR g, UCHAR b);

		COLORREF GetPixel(int x, int y);
		void SetPixel(int x, int y, COLORREF color);

		HDC GetHdc() { return mHdc; }
		HBITMAP GetBitmap() { return mBitmap; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		HBITMAP mBitmap;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;

	};
}
