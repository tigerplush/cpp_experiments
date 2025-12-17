#ifndef ARCHETYPES_H_
#define ARCHETYPES_H_

#include <unordered_map>

#include "ArchetypeComponents.hpp"

namespace ECS
{
    class Archetypes
    {
    private:
        struct ArchetypeHasher
        {
        public:
            size_t operator()(const ArchetypeComponents &archetype_components) const
            {
                size_t hash = 0;
                auto signature = archetype_components.get_signature();
                size_t index = 0;
                for (auto type_index : signature)
                {
                    size_t current_hash = std::hash<std::type_index>{}(type_index);
                    hash = hash ^ (current_hash << index);
                    index += 1;
                }
                return hash;
            }
        };

        std::unordered_map<ArchetypeComponents, size_t, ArchetypeHasher> m_archetype_to_table_id;
    public:
        bool contains(const ArchetypeComponents& archetype_components) const
        {
            return m_archetype_to_table_id.find(archetype_components) != m_archetype_to_table_id.end();
        }

        void insert(ArchetypeComponents archetype_components, size_t table_id)
        {
            m_archetype_to_table_id.emplace(archetype_components, table_id);
        }

        size_t at(const ArchetypeComponents& archetype_components) const
        {
            return m_archetype_to_table_id.at(archetype_components);
        }
    };
} // namespace ECS

#endif