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
			std::map<std::wstring, Animation*> charanis;

			std::map<std::wstring, Animation*>::iterator iter = this->mAnimations.begin();

			for (; iter != mAnimations.end(); iter++)
			{
				charanis.insert(std::make_pair(iter->first, iter->second));
			}
			return charanis;
		}

		void SetAnimations(std::map<std::wstring, Animation*> anis) 
		{ 
			std::map<std::wstring, Animation*>::iterator iter = anis.begin();
			for (; iter != anis.end(); iter++)
			{
				std::wstring first = iter->first;
				Animation* second = iter->second;
				this->mAnimations.insert(std::make_pair(first, second));
			}
		}


	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;
		Animation* mActiveAnimation;

		bool mDirection;
		bool mbLoop;
	};
}
