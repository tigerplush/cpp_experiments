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

        template <typename T>
        struct is_filter : std::false_type
        {
        };

        template <typename T>
        static constexpr bool is_component = !is_filter<T>::value;

        template <typename... Ts>
        struct filter_components;

        template <>
        struct filter_components<>
        {
            using type = std::tuple<>;
        };

        template <typename T, typename... Rest>
        struct filter_components<T, Rest...>
        {
            using rest_type = typename filter_components<Rest...>::type;
            using type = std::conditional_t<
                is_component<T>,
                decltype(std::tuple_cat(std::declval<std::tuple<T>>(), std::declval<rest_type>())),
                rest_type>;
        };

    public:
        using ComponentTuple = typename filter_components<Components...>::type;
        template <typename Tuple>
        struct tuple_to_refs;

        template <typename... Components>
        struct tuple_to_refs<std::tuple<Components...>>
        {
            // Helper to convert component type to reference or value
            template <typename T>
            using to_ref = std::conditional_t<std::is_same_v<T, Entity>, Entity, T &>;

            using type = std::tuple<to_ref<Components>...>;
        };

        using RefTuple = typename tuple_to_refs<ComponentTuple>::type;
        class Iterator
        {
        private:
            World &m_world;
            size_t m_index;

            template <size_t... Is>
            RefTuple get_components(std::index_sequence<Is...>) const
            {
                return RefTuple(m_world.get_component<std::tuple_element_t<Is, ComponentTuple>>(m_index)...);
            }

        public:
            Iterator(World &t_world, size_t t_index)
                : m_world(t_world), m_index(t_index)
            {
            }

            RefTuple operator*() const
            {
                return get_components(std::make_index_sequence<std::tuple_size_v<ComponentTuple>>{});
            }

            Iterator &operator++()
            {
                m_index += 1;
                return *this;
            }

            bool operator!=(const Iterator &other) const
            {
                return m_index != other.m_index;
            }

            bool operator==(const Iterator &other) const
            {
                return m_index == other.m_index;
            }
        };

        explicit Query(World &t_world) : m_world(t_world) {}

        Iterator begin()
        {
            return Iterator(m_world, 0);
        }

        Iterator end()
        {
            return Iterator(m_world, m_world.get_entity_count());
        }

        Iterator begin() const
        {
            return Iterator(m_world, 0);
        }

        Iterator end() const
        {
            return Iterator(m_world, m_world.get_entity_count());
        }
    };
} // namespace ECS

#endif