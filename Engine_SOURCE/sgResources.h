#pragma once
#include "sgResource.h"

namespace sg
{
	class Resources
	{
	public:
		template <typename T>
		static std::shared_ptr<T> Find(const std::wstring& key)
		{
			// 리소스 맵에서 데이터를 탐색한다. 데이터가 있다면 해당 데이터를 반환하고,
			// 없다면 end를 반환해준다.
			std::map<std::wstring, std::shared_ptr<Resource>>::iterator iter = mResources.find(key);

			// 찾고자 하는 데이터가 존재한다면, 해당 타입으로 형변환하여 반환한다.
			if (iter != mResources.end())
			{
				return std::dynamic_pointer_cast<T>(iter->second);
			}

			// 존재하지 않는다면, null을 반환
			return nullptr;
		}

		template <typename T>
		static std::shared_ptr<T> Load(const std::wstring& key, const std::wstring& path)
		{
			// 키 값(이름)으로 탐색한다.
			std::shared_ptr<T> resource = Resources::Find<T>(key);
			if (resource != nullptr)
			{
				return resource;
			}

			// 만약 위에서 찾지 못했다면 (해당 리소스가 없다면)
			// 종료된다.
			resource = std::make_shared<T>();
			if (FAILED(resource->Load(path)))
			{
				assert(false);
				return nullptr;
			}
			
			resource->SetKey(key);
			resource->SetPath(path);
			mResources.insert(std::make_pair(key, resource));

			return std::dynamic_pointer_cast<T>(resource);
		}

		template <typename T>
		static void Insert(const std::wstring& key, std::shared_ptr<T> resource)
		{
			mResources.insert(std::make_pair(key, resource));
		}

	
	private:

		static std::map<std::wstring, std::shared_ptr<Resource>> mResources;

	};

}
