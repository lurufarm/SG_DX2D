#include "sgAnimation.h"
#include "sgTime.h"
#include "sgRenderer.h"
#include "sgConstantBuffer.h"
#include "sgAnimator.h"

namespace sg
{
	Animation::Animation()
		: Resource(enums::eResourceType::Animation)
		, mAtlas(nullptr)
		, mAnimator(nullptr)
		, mSprites{}
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
	{
	}
	Animation::~Animation()
	{
	}
	void Animation::Update()
	{
	}
	void Animation::LateUpdate()
	{
		if (mbComplete)
			return;

		mTime += Time::DeltaTime();

		if (mSprites[mIndex].duration <= mTime)
		{
			mIndex++;
			mTime = 0.0f;

			if (mSprites.size() <= mIndex)
			{
				mIndex = mSprites.size() - 1;
				mbComplete = true;
			}
		}
	}
	void Animation::Render()
	{
	}
	void Animation::Create(std::wstring name
		, std::shared_ptr<graphics::Texture> atlas
		, Vector2 leftTop
		, Vector2 size
		, UINT columnLength
		, Vector2 offset
		, float duration)
	{
		SetKey(name);
		mAtlas = atlas;
		mSpriteSize = size;
		float width = atlas->GetWidth();
		float height = atlas->GetHeight();

		for (size_t i = 0; i < columnLength; i++)
		{
			Sprite sprite = {};
			sprite.leftTop.x = leftTop.x + (i * size.x) / width;
			sprite.leftTop.y = leftTop.y / height;
			sprite.size.x = mSpriteSize.x / width;
			sprite.size.y = mSpriteSize.y / height;
			sprite.offset = offset;
			sprite.atlasSize = Vector2(size.x / width, size.y / height);
			sprite.duration = duration;

			mSprites.push_back(sprite);
		}
	}
	void Animation::Binds()
	{
		// Texture Bind
		mAtlas->BindShaderResource(graphics::eShaderStage::PS, 12);

		// Animation CB
		renderer::AnimatorCB data = {};

		data.spriteLeftTop = mSprites[mIndex].leftTop;
		data.spriteSize = mSprites[mIndex].size;
		data.spriteOffset = mSprites[mIndex].offset;
		data.atlasSize = mSprites[mIndex].atlasSize;
		data.animationType = mDirection;
		data.dummydata = Vector3::Zero;
		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Animator];
		cb->SetData(&data);

		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);

	}
	void Animation::Reset()
	{
		mTime = 0.0f;
		mbComplete = false;
		mIndex = 0;
	}
}