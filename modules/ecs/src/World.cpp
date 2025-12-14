#include "World.hpp"

namespace ECS
{
    size_t World::get_entity_count() const
    {
        return m_entities.size();
    }

    size_t World::get_tables_count() const
    {
        return m_tables.size();
    }
}