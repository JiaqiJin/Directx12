#pragma once

#include "CompCommon.h"

// Macro for forward declaration
#define INIT_INFO(component) namespace component { struct InitInfo; }
INIT_INFO(Transform);
#undef INIT_INFO

namespace Kawaii::Entity
{
	struct Entity_Info
	{
		Transform::InitInfo* transform{ nullptr };
	};

	entity_id CreateEntity(Entity_Info info);
	void RemoveEntity(entity_id id);
	bool IsAlive(entity_id id);
}