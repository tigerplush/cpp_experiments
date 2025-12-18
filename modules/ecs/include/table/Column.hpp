#ifndef COLUMN_H_
#define COLUMN_H_

#include <vector>

#include "IColumn.hpp"

namespace ECS
{
    template<typename Component>
    class Column : public IColumn
    {
    private:
        std::vector<Component> m_data;
    public:
        void emplace_back(const Component& component)
        {
            m_data.emplace_back(component);
        }

        Component& get(size_t index)
        {
            return m_data[index];
        }

        const Component& get(size_t index) const
        {
            return m_data[index];
        }
    };
} // namespace ECS
#endif