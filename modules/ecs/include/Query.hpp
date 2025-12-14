#ifndef QUERY_H_
#define QUERY_H_

#include "World.hpp"
namespace ECS
{
    /// @brief Queries the world for components
    template<typename... Components>
    class Query
    {
    private:
        World& m_world;
    public:
        explicit Query(World& t_world) : m_world(t_world) {}
    };
} // namespace ECS

#endif