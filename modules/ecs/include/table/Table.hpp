#ifndef TABLE_H_
#define TABLE_H_

#include "../entity/Entity.hpp"

#include "IColumn.hpp"
#include "Column.hpp"

namespace ECS
{
    class Table
    {
    private:
        std::vector<Entity> m_entities;
        std::vector<std::unique_ptr<IColumn>> m_columns;
        std::unordered_map<std::type_index, size_t> m_component_to_column;

        template <typename Component>
        void register_component()
        {
            std::type_index component_id = std::type_index(typeid(Component));
            if (m_component_to_column.find(component_id) == m_component_to_column.end())
            {
                size_t column_id = m_columns.size();
                m_component_to_column[component_id] = column_id;
                m_columns.push_back(std::make_unique<Column<Component>>());
            }
        }

    public:
        Table(const Table&) = delete;
        Table& operator=(const Table&) = delete;

        Table(Table&&) noexcept = default;
        Table& operator=(Table&&) noexcept = default;

        template <typename... Components>
        explicit Table(Components... components)
        {
            (register_component<Components>(), ...);
        }

        template <typename... Components>
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

        const std::vector<Entity> &get_entities() const
        {
            return m_entities;
        }
    };
} // namespace ECS
#endif