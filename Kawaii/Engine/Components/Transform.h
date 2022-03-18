#pragma once

#include "CompCommon.h"

namespace Kawaii::Transform
{
	DEFINE_TYPED_ID(transform_id);

	struct InitInfo
	{
		f32 position[3]{};
		f32 rotation[4]{};
		f32 scale[3]{ 1.f, 1.f, 1.f };
	};

	transform_id Create_Transform(const InitInfo& info, Entity::Entity entity);
	void Remove_Transform();
}