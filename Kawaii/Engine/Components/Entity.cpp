#include "Entity.h"
#include "Transform.h"

namespace Kawaii::Entity
{
	namespace
	{
		Utils::vector<Id::generation_type> generations;
		Utils::deque<entity_id> free_Ids;
		Utils::vector <Transform::Component> transforms;
	}

	Entity CreateEntity(Entity_Info info)
	{
		assert(info.transform);
		if (!info.transform)
			return Entity{};

		entity_id id;

		if (free_Ids.size() > Id::min_Deleted_Elements)
		{
			id = free_Ids.front();
			assert(!IsAlive(id));
			free_Ids.pop_front();
			id = entity_id{ Id::NewGeneration(id) };
			++generations[Id::Index(id)];
		}
		else
		{
			id = entity_id{ (Id::id_type)generations.size() };
			generations.push_back(0);

			// Resize components vector to match the amount of entities
			// Using emplace_back() over resize() reduces the amount of memory allocations
			transforms.emplace_back();
		}

		const Entity newEntity{ id };
		const Id::id_type index{ Id::Index(id) };

		// Create transform component
		assert(!transforms[index].IsValid());
		transforms[index] = Transform::Create_Transform(*info.transform, newEntity);
		if (!transforms[index].IsValid()) return {};

		return newEntity;
	}

	void RemoveEntity(entity_id id)
	{
		const Id::id_type index{ Id::Index(id) };
		assert(IsAlive(id));

		Transform::Remove_Transform(transforms[index]);
		transforms[index] = {};

		free_Ids.push_back(id);
	}

	bool IsAlive(entity_id id)
	{
		assert(Id::IsValid(id));
		const Id::id_type index{ Id::Index(id) };
		assert(index < generations.size());
		return (generations[index] == Id::Generation(id) && transforms[index].IsValid());
	}

	// Entity class Method implementations
	Transform::Component Entity::Transform() const
	{
		assert(IsAlive(m_id));
		const Id::id_type index{ Id::Index(m_id) };
		return transforms[index];
	}
}