#ifndef COMMANDS_H_
#define COMMANDS_H_

#include "Component.hpp"
#include "World.hpp"

#include <iostream>

namespace ECS
{
    class Commands
    {
    private:
        World &m_world;

    public:
        explicit Commands(World& t_world);

        template<typename... Components>
        void spawn(Components... components)
        {
            m_world.spawn(components...);
        }
    };
} // namespace ECS

#endif