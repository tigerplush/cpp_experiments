#include <gtest/gtest.h>
#include "Component.hpp"
#include "ArchetypeComponents.hpp"

struct Position : public ECS::Component
{

};
struct Velocity : public ECS::Component
{

};

TEST(ArchetypeComponentTest, ArchetypeComponentEquals) {
    ECS::ArchetypeComponents lhs = ECS::ArchetypeComponents(Position {});
    ECS::ArchetypeComponents rhs = ECS::ArchetypeComponents(Position {});
    EXPECT_EQ(lhs, rhs);
}

TEST(ArchetypeComponentTest, ArchetypeComponentEqualsComplex) {
    ECS::ArchetypeComponents lhs = ECS::ArchetypeComponents(Position {}, Velocity {});
    ECS::ArchetypeComponents rhs = ECS::ArchetypeComponents(Velocity {}, Position {});
    EXPECT_EQ(lhs, rhs);
}

TEST(ArchetypeComponentTest, ArchetypeComponentNotEquals) {
    ECS::ArchetypeComponents lhs = ECS::ArchetypeComponents(Position {});
    ECS::ArchetypeComponents rhs = ECS::ArchetypeComponents(Velocity {});
    EXPECT_NE(lhs, rhs);
}

TEST(ArchetypeComponentTest, ArchetypeComponentNotEqualsComplex) {
    ECS::ArchetypeComponents lhs = ECS::ArchetypeComponents(Position {});
    ECS::ArchetypeComponents rhs = ECS::ArchetypeComponents(Velocity {}, Position {});
    EXPECT_NE(lhs, rhs);
}