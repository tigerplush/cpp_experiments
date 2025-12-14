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

        template<typename T>
        void spawn(T&& component)
        {
            m_world.spawn();
        }
    };
} // namespace ECS

#endif