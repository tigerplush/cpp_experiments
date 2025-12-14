#include "World.hpp"

namespace ECS
{
    size_t World::get_entity_count() const
    {
        return m_entities.size();
    }
}