#ifndef ENTITY_H_
#define ENTITY_H_

#include <ostream>

namespace ECS
{
    struct Entity
    {
    private:
        size_t m_id;

    public:
        Entity(size_t t_id)
            : m_id(t_id)
        {
        }

        friend std::ostream &operator<<(std::ostream &os, const Entity &entity)
        {
            return os << "Entity(" << entity.m_id << ")";
        }
    };
} // namespace ECS

#endif