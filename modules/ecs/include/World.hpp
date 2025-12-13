#ifndef WORLD_H_
#define WORLD_H_

#include "Commands.hpp"
#include "Query.hpp"

namespace ECS
{
    class World
    {
    private:
        template <typename T>
        static constexpr bool always_false = false;

    public:
        template <typename Args>
        Args create()
        {
            using T = std::decay_t<Args>;

            if constexpr (std::is_same_v<T, ECS::Commands>)
            {
                return Commands();
            }
            else if constexpr (std::is_same_v<T, ECS::Query>)
            {
                return Query();
            }
            else
            {
                static_assert(always_false<Args>, "Unsupported system parameter type");
            }
        }
    };
} // namespace World

#endif