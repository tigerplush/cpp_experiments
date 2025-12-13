#include <iostream>

#include "App.hpp"
#include "Commands.hpp"
#include "Query.hpp"

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

void print_hello_world(ECS::Query query)
{
    std::cout << "Loop" << std::endl;
}

int main()
{
    App::App()
        .add_system(App::Schedule::Startup, startup)
        .add_system(App::Schedule::Update, print_hello_world)
        .run();
}