#include "sgEntity.h"


namespace sg
{
	Entity::Entity()
		: mName(L"")
		, mColliderID((UINT64)this)
	{

	}
	Entity::~Entity()
	{
	}
}