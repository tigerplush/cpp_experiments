#include <functional>
#include <vector>

namespace App
{
    struct ScheduleLabel
    {
    private:
        const char* m_label;
    public:
        explicit ScheduleLabel(const char* t_label) : m_label(t_label)
        {
        }

        friend bool operator<(const ScheduleLabel& lhs, const ScheduleLabel& rhs)
        {
            return std::strcmp(lhs.m_label, rhs.m_label) < 0;
        }
    };

    struct Schedule
    {
        inline static const ScheduleLabel Startup {"Startup"};
        inline static const ScheduleLabel Update {"Update"};
    };

    struct ScheduleRunner
    {
    private:
        const std::vector<ScheduleLabel> m_startup_labels = std::vector<ScheduleLabel>{ Schedule::Startup };
        const std::vector<ScheduleLabel> m_labels = std::vector<ScheduleLabel> { Schedule::Update };
    public:
        void run(std::function<void(const ScheduleLabel&)> callback)
        {
            for(auto startup_label: m_startup_labels)
            {
                callback(startup_label);
            }
            for(;;)
            {
                for(auto label: m_labels)
                {
                    callback(label);
                }
            }
        }
    };

} // namespace App
