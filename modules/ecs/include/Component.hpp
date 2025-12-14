#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <ostream>

namespace ECS
{
    /// @brief This is the base component all components have to derive
    struct Component
    {
        size_t hash() const
        {
            return typeid(*this).hash_code();
        }
        virtual std::string to_string() const
        {
            return "Component";
        }

        friend std::ostream &operator<<(std::ostream &os, const Component &component)
        {
            return os << component.to_string();
        }
    };
} // namespace ECS

#endif