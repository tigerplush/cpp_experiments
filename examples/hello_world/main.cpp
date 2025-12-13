#include <iostream>

#include "App.hpp"

void print_hello_world()
{
    std::cout << "Hello World" << std::endl;
}

int main()
{
    App::App()
        .add_system(App::Schedule::Update, print_hello_world)
        .run();
}
