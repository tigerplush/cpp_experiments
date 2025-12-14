#include "World.hpp"

namespace ECS
{
    size_t World::spawn()
    {
        size_t current_id = m_next_id;
        m_entities.push_back(current_id);
        m_next_id += 1;
        return current_id;
    }
}