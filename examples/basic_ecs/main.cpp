#include <iostream>
#include <sstream>

#include "App.hpp"
#include "ECS.hpp"
#include "Log.hpp"

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
    Log::DEBUG << "Startup";
    commands.spawn(Position {});
    commands.spawn(Position(5, 5));
}

void print_hello_world(ECS::Query<ECS::Entity, Position> query)
{
    Log::DEBUG << "There are " << query.count() << " entities that fit the query";
    for(auto [entity, position]: query)
    {
        Log::DEBUG << entity << " has position " << position;
        position.x += 1;
        position.y += 1;
    }
}

int main()
{
    Log::Logger::get_instance().set_log_level(LogLevel::Debug);
    App::App()
        .add_system(App::Schedule::Startup, startup)
        .add_system(App::Schedule::Update, print_hello_world)
        .run();
}