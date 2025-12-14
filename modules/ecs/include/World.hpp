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
        /// @brief Returns the number of all currently active entities
        /// @return 
        size_t get_entity_count() const;
    };
} // namespace World

#endif