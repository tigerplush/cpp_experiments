#include "app.hpp"

namespace App
{
    void App::run()
    {
    }

    App &App::add_system(const ScheduleLabel& schedule, std::function<void()> system)
    {
        return *this;
    }
} // namespace App
