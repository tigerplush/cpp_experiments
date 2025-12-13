#include <iostream>

#include "App.hpp"
#include "Commands.hpp"
#include "Query.hpp"

void startup(ECS::Commands& commands)
{
    std::cout << "Startup" << std::endl;
}

void print_hello_world(ECS::Query)
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
