#ifndef APP_H_
#define APP_H_

#include <map>
#include <functional>
#include <tuple>
#include <type_traits>
#include <vector>

#include "ECS.hpp"

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
            auto args = std::tuple{create<std::remove_reference_t<typename Traits::template arg<Is>::type>>(ctx)...};
            // Apply the function with the stored objects
            std::apply(system, args);
        }

        template <typename T>
        static constexpr bool always_false = false;


        template<typename T>
        struct is_query : std::false_type {};

        template<typename... Components>
        struct is_query<ECS::Query<Components...>> : std::true_type {};

        template <typename Args>
        static Args create(ECS::World& world)
        {
            using T = std::decay_t<Args>;

            if constexpr (std::is_same_v<T, ECS::Commands>)
            {
                return ECS::Commands(world);
            }
            else if constexpr (is_query<T>::value)
            {
                return T(world);
            }
            else
            {
                static_assert(always_false<Args>, "Unsupported system parameter type");
            }
        }

    public:
        /// @brief 
        /// @tparam Fn 
        /// @param schedule 
        /// @param system 
        /// @return 
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

        /// @brief runs all registered plugins and systems
        void run();
    };
} // namespace App

#endif