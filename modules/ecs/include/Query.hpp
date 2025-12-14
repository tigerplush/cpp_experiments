#ifndef QUERY_H_
#define QUERY_H_

#include "World.hpp"

#include "Core.hpp"

namespace ECS
{
    /// @brief Queries the world for components
    template <typename... Components>
    class Query : public Core::IterableBase<Query<Components...>>
    {
    private:
        World &m_world;

    public:
        class Iterator
        {
        public:
            Iterator(size_t t_index) : m_index(t_index)
            {
            }

            size_t operator*() const
            {
                return m_index;
            }

            Iterator& operator++()
            {
                m_index += 1;
                return *this;
            }

            bool operator!=(const Iterator& other) const
            {
                return m_index != other.m_index;
            }

            bool operator==(const Iterator& other) const
            {
                return m_index == other.m_index;
            }

        private:
            size_t m_index;
        };

        explicit Query(World &t_world) : m_world(t_world) {}

        Iterator begin()
        {
            return Iterator(0);
        }

        Iterator end()
        {
            return Iterator(m_world.get_entity_count());
        }

        Iterator begin() const
        {
            return Iterator(0);
        }

        Iterator end() const
        {
            return Iterator(m_world.get_entity_count());
        }
    };
} // namespace ECS

#endif