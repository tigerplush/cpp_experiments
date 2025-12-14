#ifndef WORLD_H_
#define WORLD_H_

#include <iostream>

#include <vector>

#include "ArchetypeComponents.hpp"
#include "entity/Entity.hpp"
namespace ECS
{
    class World
    {
    private:
        std::vector<Entity> m_entities;
        size_t m_next_id = 0;

    public:
        template<typename... Components>
        Entity spawn(Components... components)
        {
            // First of all, create an archetype of the given components
            // For that we take the component type and hash it
            // so now we have a unique hash per component type
            // if we call .spawn(Position, Velocity) we get the same archetype as when
            // we call .spawn(Position, Velocity) again
            // if we call .spawn(Position, Name)
            // we get a different archetype
            ArchetypeComponents archetype_components = ArchetypeComponents(components...);

            // now, we look up, if a table for this archetype already exists
            // if yes, we add the entity and it's components to that table
            // if no, we create a new table with the given archetype and add entity and components to that

            Entity current = Entity(m_next_id);
            m_entities.push_back(current);
            m_next_id += 1;
            return current;
        }
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