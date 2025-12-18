#ifndef TABLE_H_
#define TABLE_H_

#include "../ComponentId.hpp"
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
        void register_component(Component component)
        {
            ComponentId component_id = ComponentId::from<Component>();
            if (m_component_to_column.find(component_id.id()) == m_component_to_column.end())
            {
                size_t column_id = m_columns.size();
                m_component_to_column[component_id.id()] = column_id;
                m_columns.push_back(std::make_unique<Column<Component>>());
            }
        }

        template<typename Component>
        void set_component(size_t row, Component&& value)
        {
            ComponentId component_id = ComponentId::from<Component>();
            size_t column_id = m_component_to_column[component_id.id()];

            Column<Component>* column = static_cast<Column<Component>*>(m_columns[column_id].get());
            column->emplace_back(value);
        }

    public:
        Table(const Table&) = delete;
        Table& operator=(const Table&) = delete;

        Table(Table&&) noexcept = default;
        Table& operator=(Table&&) noexcept = default;

        template <typename... Components>
        explicit Table(Components... components)
        {
            (register_component<Components>(components), ...);
        }

        template <typename... Components>
        size_t add(Entity entity, Components... components)
        {
            size_t table_row = m_entities.size();
            m_entities.push_back(entity);
            (set_component(table_row, std::move(components)), ...);
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

        template<typename Component>
        Component& get_component(size_t row)
        {
            ComponentId component_id = ComponentId::from<Component>();
            size_t column_id = m_component_to_column.at(component_id.id());
            Column<Component>* column = static_cast<Column<Component>*>(m_columns[column_id].get());
            return column->get(row);
        }
        
        template<typename Component>
        const Component& get_component(size_t row) const
        {
            ComponentId component_id = ComponentId::from<Component>();
            size_t column_id = m_component_to_column.at(component_id.id());
            Column<Component>* column = static_cast<Column<Component>*>(m_columns[column_id].get());
            return column->get(row);
        }
    };
} // namespace ECS
#endif