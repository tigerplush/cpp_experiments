#include "World.hpp"

namespace ECS
{
    Entity World::spawn()
    {
        Entity current = Entity(m_next_id);
        m_entities.push_back(current);
        m_next_id += 1;
        return current;
    }

    size_t World::get_entity_count() const
    {
        return m_entities.size();
    }
}