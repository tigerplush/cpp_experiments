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
    };
} // namespace ECS
#endif