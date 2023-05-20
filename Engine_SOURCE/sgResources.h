#pragma once
#include "sgResource.h"

namespace sg
{
	class Resources
	{
	public:
		template <typename T>
		static T* Finde(const std::wstring& key)
		{
			// ���ҽ� �ʿ��� �����͸� Ž���Ѵ�. �����Ͱ� �ִٸ� �ش� �����͸� ��ȯ�ϰ�,
			// ���ٸ� end�� ��ȯ���ش�.
			std::map<std::wstring, Resource*>::iterator iter = mResources.find(key);

			// ã���� �ϴ� �����Ͱ� �����Ѵٸ�, �ش� Ÿ������ ����ȯ�Ͽ� ��ȯ�Ѵ�.
			if (iter != mResources.end())
			{
				return dynamic_cast<T*>(iter->second);
			}

			// �������� �ʴ´ٸ�, null�� ��ȯ
			return nullptr;
		}

		template <typename T>
		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			// Ű ��(�̸�)���� Ž���Ѵ�.
			T* resource = Resources::Finde<T>(key);
			if (resource != nullptr)
			{
				return resource;
			}

			// ���� ������ ã�� ���ߴٸ� (�ش� ���ҽ��� ���ٸ�)
			// ����ȴ�.
			resource = new T();
			if (FAILED(resource->Load(path)))
			{
				assert(false);
				return nullptr;
			}
			
			resource->SetKey(key);
			resource->SetPath(path);
			mResources.insert(std::make_pair(key, resource));

			return dynamic_cast<T*>(resource);
		}

		template <typename T>
		static void Insert(const std::wstring& key, T* resource)
		{
			mResources.insert(std::make_pair(key, resource));
		}

		static void Release()
		{
			for (auto pair : mResources)
			{
				delete pair.second;
				pair.second = nullptr;
			}
		}

	
	private:

		static std::map<std::wstring, Resource*> mResources;

	};

}
