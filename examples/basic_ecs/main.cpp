#include <iostream>
#include <sstream>

#include "App.hpp"
#include "ECS.hpp"

struct Position : public ECS::Component
{
    int x;
    int y;
    Position(int t_x = 0, int t_y = 0) : x(t_x), y(t_y){}
    virtual std::string to_string() const override
    {
        std::ostringstream oss;
        oss << "Position {" << x << ", " << y << "}";
        return oss.str();
    }
};

void startup(ECS::Commands& commands)
{
    std::cout << "Startup" << std::endl;
    commands.spawn(Position {});
    commands.spawn(Position(5, 5));
}

void print_hello_world(ECS::Query<ECS::Entity, Position> query)
{
    std::cout << "There are " << query.count() << " entities that fit the query" << std::endl;
    for(auto [entity, position]: query)
    {
        std::cout << entity << " has position " << position << std::endl;
        position.x += 1;
        position.y += 1;
    }
}

int main()
{
    App::App()
        .add_system(App::Schedule::Startup, startup)
        .add_system(App::Schedule::Update, print_hello_world)
        .run();
}