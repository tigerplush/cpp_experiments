#include <gtest/gtest.h>
#include "Component.hpp"
#include "World.hpp"

struct Position : public ECS::Component
{

};
struct Velocity : public ECS::Component
{

};

TEST(WorldTest, SpawnComponents) {
    ECS::World world;
    world.spawn(Position {});
    EXPECT_EQ(world.get_entity_count(), 1);
    EXPECT_EQ(world.get_tables_count(), 1);
    world.spawn(Velocity {});
    EXPECT_EQ(world.get_entity_count(), 2);
    EXPECT_EQ(world.get_tables_count(), 2);
    world.spawn(Velocity {});
    EXPECT_EQ(world.get_entity_count(), 3);
    EXPECT_EQ(world.get_tables_count(), 2);
}
