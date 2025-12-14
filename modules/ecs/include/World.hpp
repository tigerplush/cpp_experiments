#ifndef WORLD_H_
#define WORLD_H_

#include <vector>

namespace ECS
{
    class World
    {
    private:
        std::vector<size_t> m_entities;
        size_t m_next_id = 0;

    public:
        size_t spawn();
    };
} // namespace World

#endif