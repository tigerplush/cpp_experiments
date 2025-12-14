#ifndef ARCHETYPE_COMPONENTS_H_
#define ARCHETYPE_COMPONENTS_H_

#include <ostream>
#include <set>
#include <typeindex>

namespace ECS
{
    class ArchetypeComponents
    {
    private:
        std::set<std::type_index> m_signature;
    public:
        template<typename... Components>
        ArchetypeComponents(Components... components)
        {
            m_signature = { std::type_index(typeid(Components))...};
        }

        bool operator==(const ArchetypeComponents &other) const
        {
            return m_signature == other.m_signature;
        }

        friend std::ostream &operator<<(std::ostream &os, const ArchetypeComponents &archetype_components)
        {
            if(archetype_components.m_signature.empty())
            {
                os << "{}";
                return os;
            }
            os << "{ ";
            size_t index = 0;
            for(auto type_index: archetype_components.m_signature)
            {
                if(0 != index)
                {
                    os << ", ";
                }
                os << type_index.name();
            }
            os << " }";
            return os;
        }
    };
} // namespace ECS

#endif