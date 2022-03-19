#pragma once

#include "CompCommon.h"

namespace Kawaii::Transform
{
	struct InitInfo
	{
		f32 position[3]{};
		f32 rotation[4]{};
		f32 scale[3]{ 1.f, 1.f, 1.f };
	};

	Transform::Component Create_Transform(const InitInfo& info, Entity::Entity entity);
	void Remove_Transform(Component component);
}