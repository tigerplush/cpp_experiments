#ifndef WORLD_H_
#define WORLD_H_

#include <vector>

#include "Entity.hpp"
namespace ECS
{
    class World
    {
    private:
        std::vector<Entity> m_entities;
        size_t m_next_id = 0;

    public:
        Entity spawn();
        /// @brief Returns the number of all currently active entities
        size_t get_entity_count() const;

        template<typename Component>
        Component& get_component(size_t entity_index)
        {
            if constexpr (std::is_same_v<Component, Entity>)
            {
                return m_entities.at(entity_index);
            }
            else
            {
                static Component dummy;
                return dummy;
            }
        }
    };
} // namespace World

#endif