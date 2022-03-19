#pragma once

#include "CompCommon.h"

namespace Kawaii
{
	// Macro for forward declaration
#define INIT_INFO(component) namespace component { struct InitInfo; }
	INIT_INFO(Transform);
#undef INIT_INFO

	struct Entity_Info
	{
		Transform::InitInfo* transform{ nullptr };
	};

	namespace Entity
	{
		Entity CreateEntity(Entity_Info info);
		void RemoveEntity(entity_id id);
		bool IsAlive(entity_id id);
	}
}