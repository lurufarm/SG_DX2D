#include "sgPaintShader.h"
#include "sgTexture.h"

namespace sg::graphics
{
	void PaintShader::Binds()
	{
		mTarget->BindUnorderedAccessViews(0);

		mGroupX = (UINT)mTarget->GetWidth() / mThreadGroupCountX + 1;
		mGroupX = (UINT)mTarget->GetHeight() / mThreadGroupCountY + 1;
		mGroupZ = 1;
	}
	void PaintShader::Clear()
	{
		mTarget->ClearUnorderedAccessViews(0);
	}
}