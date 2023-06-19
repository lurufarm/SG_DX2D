#pragma once
#include "sgEntity.h"
#include "sgComponent.h"

namespace sg
{
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		template <typename T>
		T* GetComp()
		{
			T* component;
			for (Component* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					return component;
			}
			
			return nullptr;
		}

		template <typename T>
		T* AddComp()
		{
			T* comp = new T();

			Component* buff
				= dynamic_cast<Component*>(comp);

			if (buff == nullptr)
				return nullptr;

			mComponents.push_back(buff);
			comp->SetOwner(this);

			return comp;
		}

	private:
		eState mState;
		std::vector<Component*> mComponents;
	};
}
