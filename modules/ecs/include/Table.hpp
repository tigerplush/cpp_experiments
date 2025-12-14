#ifndef TABLE_H_
#define TABLE_H_

#include "entity/Entity.hpp"

namespace ECS
{
    class Table
    {
    private:
        std::vector<Entity> m_entities;
    public:
        template<typename... Components>
        size_t add(Entity entity, Components... components)
        {
            size_t table_row = m_entities.size();
            m_entities.push_back(entity);
            return table_row;
        }

        size_t get_entity_count() const
        {
            return m_entities.size();
        }

        const std::vector<Entity>& get_entities() const
        {
            return m_entities;
        }
    };
} // namespace ECS
#endif