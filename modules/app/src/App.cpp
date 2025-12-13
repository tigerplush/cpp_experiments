#include "app.hpp"

namespace App
{
    void App::run()
    {
        m_scheduleRunner.run([this](const ScheduleLabel& schedule) {
            for(auto system: m_systems[schedule])
            {
                system();
            }
        });
    }

    App &App::add_system(const ScheduleLabel& schedule, std::function<void()> system)
    {
        if(m_systems.find(schedule) != m_systems.end())
        {
            m_systems[schedule].push_back(system);
        }
        else
        {
            m_systems[schedule] = std::vector<std::function<void()>> { system };
        }
        return *this;
    }
} // namespace App
