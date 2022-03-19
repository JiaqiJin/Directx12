#pragma once

#include "Common/Common.h"
#include "TransformComponent.h"

namespace Kawaii::Entity
{
	DEFINE_TYPED_ID(entity_id);

	class Entity
	{
	public:
		constexpr Entity() : m_id{ Id::INVALID_ID } {}
		constexpr explicit Entity(entity_id id) : m_id{ id } {}
		constexpr entity_id GetID() const { return m_id; }
		constexpr bool IsValid() const { return Id::IsValid(m_id); }

		Transform::Component Transform() const;
	private:
		entity_id m_id;
	};
}