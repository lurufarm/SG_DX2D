#pragma once
#include "sgResource.h"
#include "sgTexture.h"

namespace sg
{
	using namespace math;
	using namespace graphics;

	class Animator;
	class Animation : public Resource
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;
			Vector2 size;
			Vector2 offset;
			Vector2 atlasSize;
			float duration;

			Sprite()
				: leftTop(Vector2::Zero)
				, size(Vector2::Zero)
				, offset(Vector2::Zero)
				, atlasSize(Vector2::Zero)
				, duration(0.0f)
			{

			}
		};

		Animation();
		~Animation();

		virtual HRESULT Load(const std::wstring& path) { return S_FALSE; }

		void Update();
		void LateUpdate();
		void Render();

		void Create(std::wstring name
			, std::shared_ptr<graphics::Texture> atlas
			, Vector2 leftTop
			, Vector2 size
			, UINT columnLength
			, Vector2 offset = Vector2::Zero
			, float duration = 0.0f);
		
		void Binds();
		void Reset();

		bool IsComplete() { return mbComplete; }
		int GetAniIndex() { return mIndex; }
		void SetAniDirection(bool direction) { mDirection = direction; }
		bool GetAniDirection() { return mDirection; }

		Vector2 GetSpriteSize() { return mSpriteSize; }
		int GetmSpritesSize() { return mSprites.size(); }
		std::shared_ptr<graphics::Texture> GetAtlas() { return mAtlas; }
		void SetAtlas(std::shared_ptr<graphics::Texture> atlas) { mAtlas = atlas; }

	private:
		std::shared_ptr<graphics::Texture> mAtlas;
		Animator* mAnimator;
		std::vector<Sprite> mSprites;
		int mIndex;
		float mTime;
		bool mbComplete;

		bool mDirection;

		Vector2 mSpriteSize;

	};
}
