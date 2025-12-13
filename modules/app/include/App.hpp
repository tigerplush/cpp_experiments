#include <map>
#include <functional>
#include <vector>

#include "Schedule.hpp"

namespace App
{
    /// This is the entry point of the engine.
    ///
    /// # Example
    /// ```
    /// void main()
    /// {
    ///     App()
    ///         .add_system(print_hello_world)
    ///         .run();
    /// }
    /// 
    /// void print_hello_world()
    /// {
    ///     println("Hello World");
    /// }
    /// ```
    class App
    {
    private:
        std::map<ScheduleLabel, std::vector<std::function<void()>>> m_systems;
        ScheduleRunner m_scheduleRunner;
    public:

        template<typename Fn>
        App &add_system(const ScheduleLabel& schedule, Fn&& system)
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

        void run();
    };
} // namespace App
