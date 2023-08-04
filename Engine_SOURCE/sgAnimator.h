#pragma once
#include "sgComponent.h"
#include "sgAnimation.h"

namespace sg
{
	class Animator : public Component
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}

			void operator()()
			{
				if (mEvent)
					mEvent();
			}

			std::function<void()> mEvent;
		};

		struct Events
		{
			Event startEvent;
			Event completeEvent;
			Event endEvent;
		};

		Animator();
		~Animator();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void Create(std::wstring name
			, std::shared_ptr<graphics::Texture>atlas
			, Vector2 leftTop
			, Vector2 size
			, UINT columnLength
			, Vector2 offset = Vector2::Zero
			, float duration = 0.0f);
		Animation* FindAnimation(const std::wstring& name);
		Events* FindEvents(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop, bool direction);
		void Binds();

		std::function<void()>& StartEvent(const std::wstring key);
		std::function<void()>& CompleteEvent(const std::wstring key);
		std::function<void()>& EndEvent(const std::wstring key);

		std::map<std::wstring, Animation*> GetAnimations()
		{
			return mAnimations; // map 복사 생성자가 호출되어 mAnimations의 애니메이션들을 복사하여 반환합니다.
		}

		void SetAnimations(const std::map<std::wstring, Animation*>& anis)
		{
			for (auto& iter : mAnimations)
			{
				delete iter.second;
			}
			mAnimations.clear(); 

			for (auto& iter : anis)
			{
				std::wstring first = iter.first;
				Animation* second = new Animation(*(iter.second));
				mAnimations.insert(std::make_pair(first, second));
			}
		}

		Vector2 GetAnimationScale() { return mAnimations.begin()->second->GetSpriteSize(); }
		Animation* GetActiveAni() { return mActiveAnimation; }

		std::shared_ptr<Texture> GetAniTexture() { return mAnimations.begin()->second->GetAtlas(); }
		void SetAniTexture(std::shared_ptr<Texture> atlas)
		{
			for (auto& iter : mAnimations)
			{
				iter.second->SetAtlas(atlas);
			}
		}

	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;
		Animation* mActiveAnimation;
		Animation* mPrevAni;

		bool mDirection;
		bool mbLoop;
	};
}
