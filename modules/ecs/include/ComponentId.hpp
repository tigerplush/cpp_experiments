#ifndef COMPONENT_ID_H_
#define COMPONENT_ID_H_

#include <typeindex>
#include <ostream>

namespace ECS
{
    struct ComponentId
    {
    private:
        std::type_index m_component_id;
        ComponentId(std::type_index t_component_id) : m_component_id(t_component_id) {}
    public:
        template<typename Component>
        static ComponentId from()
        {
            return ComponentId(typeid(Component));
        }

        const std::type_index id() const
        {
            return m_component_id;
        }

        friend std::ostream &operator<<(std::ostream &os, const ComponentId &componentId)
        {
            return os << "ComponentId( name: " << componentId.m_component_id.name() << ", id: " << componentId.m_component_id.hash_code() << ")";
        }
    };
} // namespace ECS


#endif