#include "app.hpp"

namespace App
{
    void App::run()
    {
        m_scheduleRunner.run([this](const ScheduleLabel& schedule) {
            for(auto system: m_systems[schedule])
            {
                system(m_world);
            }
        });
    }

} // namespace App
