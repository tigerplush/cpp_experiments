#include <functional>

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
    public:
        App &add_system(const ScheduleLabel& schedule, std::function<void()> system);
        void run();
    };
} // namespace App
