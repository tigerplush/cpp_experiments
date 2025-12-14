#include <iostream>

#include "App.hpp"
#include "ECS.hpp"

struct Position : public ECS::Component
{
    int x;
    int y;
};

void startup(ECS::Commands& commands)
{
    std::cout << "Startup" << std::endl;
    commands.spawn(Position {});
}

void print_hello_world(ECS::Query<ECS::Entity, Position> query)
{
    std::cout << "There are " << query.count() << " entities that fit the query" << std::endl;
    for(auto [entity, position]: query)
    {
        std::cout << entity << " has position " << position << std::endl;
    }
}

int main()
{
    App::App()
        .add_system(App::Schedule::Startup, startup)
        .add_system(App::Schedule::Update, print_hello_world)
        .run();
}