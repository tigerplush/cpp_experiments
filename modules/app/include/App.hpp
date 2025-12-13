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
        App &add_system(const ScheduleLabel& schedule, std::function<void()> system);
        void run();
    };
} // namespace App
