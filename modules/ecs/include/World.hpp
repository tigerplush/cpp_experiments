#ifndef WORLD_H_
#define WORLD_H_

#include <iostream>
#include <unordered_map>
#include <vector>

#include "archetype/Archetypes.hpp"
#include "entity/Entity.hpp"
#include "entity/EntityMetaData.hpp"
#include "table/Table.hpp"
namespace ECS
{
    class World
    {
    private:

        std::vector<EntityMetaData> m_entities;
        Archetypes m_archetypes;
        std::vector<Table> m_tables;
        size_t m_next_id = 0;

    public:
        template <typename... Components>
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

            Entity current = Entity(m_next_id);
            m_next_id += 1;
            size_t table_id = -1;
            // now, we look up, if a table for this archetype already exists
            if (!m_archetypes.contains(archetype_components))
            {
                // Table table(components...);
                table_id = m_tables.size();
                // m_tables.push_back(std::move(table));
                m_tables.emplace_back(components...);
                // if no, we create a new table with the given archetype and add entity and components to that
                m_archetypes.insert(archetype_components, table_id);
            }
            else
            {
                table_id = m_archetypes.at(archetype_components);
            }
            // after that, we can add the entity and its components
            size_t table_row = m_tables.at(table_id).add(current, components...);

            m_entities.push_back(EntityMetaData(table_id, table_row));

            return current;
        }
        /// @brief Returns the number of all currently active entities
        size_t get_entity_count() const;
        size_t get_tables_count() const;

        template <typename Component>
        auto get_component(size_t entity_index) -> std::conditional_t<std::is_same_v<std::decay_t<Component>, Entity>, Entity, Component>
        {
            EntityMetaData entity_meta = m_entities.at(entity_index);
            Table &table = m_tables.at(entity_meta.table_id);
            if constexpr (std::is_same_v<std::decay_t<Component>, Entity>)
            {
                return table.get_entities().at(entity_meta.table_row);
            }
            else
            {
                return table.get_component<std::decay_t<Component>>(entity_meta.table_row);
            }
        }
    };
} // namespace World

#endif