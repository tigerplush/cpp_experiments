#ifndef COMMAND_H_
#define COMMAND_H_

#include "Component.hpp"

#include <iostream>

namespace ECS
{
    class Commands
    {
    public:
        template<typename T>
        void spawn(T&& component)
        {
        }
    };
} // namespace ECS

#endif