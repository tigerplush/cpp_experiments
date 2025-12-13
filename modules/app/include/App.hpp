#ifndef APP_H_
#define APP_H_

#include <map>
#include <functional>
#include <tuple>
#include <type_traits>
#include <vector>

#include "World.hpp"

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
        std::map<ScheduleLabel, std::vector<std::function<void(ECS::World &)>>> m_systems;
        ScheduleRunner m_scheduleRunner;
        ECS::World m_world;

        template <typename T>
        struct function_traits;

        template <typename Ret, typename... Args>
        struct function_traits<Ret (*)(Args...)>
        {
            static constexpr size_t arity = sizeof...(Args);
            template <size_t N>
            struct arg
            {
                using type = std::tuple_element_t<N, std::tuple<Args...>>;
            };
        };

        template <typename Ret, typename... Args>
        struct function_traits<Ret(Args...)>
        {
            static constexpr size_t arity = sizeof...(Args);
            template <size_t N>
            struct arg
            {
                using type = std::tuple_element_t<N, std::tuple<Args...>>;
            };
        };

        template <typename Fn, typename... Args>
        static void call_with_params(Fn &system, ECS::World &ctx)
        {
            using Traits = function_traits<Fn>;
            call_with_indices(system, ctx, std::make_index_sequence<Traits::arity>{});
        }

        template <typename Fn, size_t... Is>
        static void call_with_indices(Fn &system, ECS::World &ctx, std::index_sequence<Is...>)
        {
            using Traits = function_traits<Fn>;
            // Create a tuple to store the objects
            auto args = std::tuple{ctx.create<std::remove_reference_t<typename Traits::template arg<Is>::type>>()...};
            // Apply the function with the stored objects
            std::apply(system, args);
        }

    public:
        template <typename Fn>
        App &add_system(const ScheduleLabel &schedule, Fn &&system)
        {

            auto wrapper = [system = std::forward<Fn>(system)](ECS::World &world) mutable
            {
                call_with_params(system, world);
            };

            m_systems[schedule].push_back(std::move(wrapper));
            return *this;
        }

        void run();
    };
} // namespace App

#endif