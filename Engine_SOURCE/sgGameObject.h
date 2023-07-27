#pragma once
#include "sgEntity.h"
#include "sgResources.h"
#include "sgComponent.h"
#include "sgMeshRenderer.h"
#include "sgScript.h"

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

		//void SetFocused(bool value) { mFocused = value; }
		//bool GetFocused() { return mFocused; }


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
			
			for (Script* script : mScripts)
			{
				component = dynamic_cast<T*>(script);
				
				if (component != nullptr)
					return component;
			}

			return nullptr;
		}

		template <typename T>
		//std::vector<T*>& GetComps()
		std::vector<T*> GetComps()
		{
			std::vector<T*> comps;

			T* component;
			for (Component* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					comps.push_back(component);
			}

			for (Script* script : mScripts)
			{
				component = dynamic_cast<T*>(script);
				if (component != nullptr)
					comps.push_back(component);
			}

			return comps;
		}

		template <typename T>
		std::vector<T*> GetComps2(std::vector<T*> comps)
		{
			//std::vector<T*> comps;

			T* component;
			for (Component* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					//comps.push_back(component);
					comps.push_back(component);
			}

			for (Script* script : mScripts)
			{
				component = dynamic_cast<T*>(script);
				if (component != nullptr)
					//comps.push_back(component);
					comps.push_back(component);
			}

			return comps;
		}

		
		template <typename T>
		T* AddComp()
		{
			T* comp = new T();

			Component* buff
				= dynamic_cast<Component*>(comp);
			Script* script
				= dynamic_cast<Script*>(buff);

			if (buff == nullptr)
				return nullptr;

			if (script == nullptr)
				mComponents.push_back(buff);
			else
				mScripts.push_back(script);
		
			comp->SetOwner(this);
			comp->Initialize();

			return comp;
		}

		void SetState(eState state) { mState = state; }
		eState GetState() { return mState; }

		virtual void SetMesh()
		{
			if (GetComp<MeshRenderer>() != nullptr)
				this->GetComp<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		}
		virtual void SetMaterial(const std::wstring& key)
		{
			if (GetComp<MeshRenderer>() != nullptr)
				this->GetComp<MeshRenderer>()->SetMaterial(Resources::Find<Material>(key));
		}


		void SetOrder(int value) { mOrder = value; }
		int GetOrder() { return mOrder; }

		std::vector<Component*> GetComponenetsVector() { return mComponents; }

		void SetSelected(bool value) { mbSelected = value; }
		bool GetSelected() { return mbSelected; }

	private:
		eState mState;
		std::vector<Component*> mComponents;
		std::vector<Script*> mScripts;
		int mOrder;
		bool mbSelected;
	};
}
